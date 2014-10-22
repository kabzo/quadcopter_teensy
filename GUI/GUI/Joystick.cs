using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.DirectX.DirectInput;


namespace GUI {
  public class Joystick {
    private Device joystickDevice;
    private JoystickState state;

    private int axisCount;
    public int oldX = 0;
    public int oldY = 0;
    public int oldZ = 0;
    public int oldRy = 0;

    public int roll = 0;
    public int pitch = 0;
    public int throttle = 0;
    public int yaw = 0;

    public int rollMax { get; set; }

    public int rollMin { get; set; }

    public int pitchMax { get; set; }

    public int pitchMin { get; set; }

    public int throttleMax { get; set; }

    public int throttleMin { get; set; }

    public int yawMax { get; set; }

    public int yawMin { get; set; }



    /// <summary>
    /// Number of axes on the joystick.
    /// </summary>
    public int AxisCount {
      get { return axisCount; }
    }

    private int axisX;
    public int AxisX {
      get { return axisX; }
    }

    private int axisY;
    public int AxisY {
      get { return axisY; }
    }

    private int axisZ;
    public int AxisZ {
      get { return axisZ; }
    }

    private int axisRy;
    public int AxisRy {
      get { return axisRy; }
    }

    private int axisE;
    public int AxisE {
      get { return axisE; }
    }

    private int axisF;
    public int AxisF {
      get { return axisF; }
    }

    private IntPtr hWnd;

    private bool[] buttons;
    public bool[] Buttons {
      get { return buttons; }
    }

    private string[] systemJoysticks;

    /// <summary>
    /// Constructor for the class.
    /// </summary>
    /// <param name="window_handle">Handle of the window which the joystick will be "attached" to.</param>
    public Joystick(IntPtr window_handle) {
      throttleMax = 56433;
      throttleMin = 10495;
      pitchMax = 53572;
      pitchMin = 8703;
      rollMax = 56173;
      rollMin = 7423;
      yawMin = 7167;
      yawMax = 52273;

      hWnd = window_handle;
      axisX = -1;
      axisY = -1;
      axisZ = -1;
      axisRy = -1;
      axisE = -1;
      axisF = -1;
      axisCount = 0;
    }

    private void Poll() {
      try {
        // poll the joystick
        joystickDevice.Poll();
        // update the joystick state field
        state = joystickDevice.CurrentJoystickState;
      } catch (Exception err) {
        // we probably lost connection to the joystick
        // was it unplugged or locked by another application?
        Console.WriteLine("Poll()");
        Console.WriteLine(err.Message);
        Console.WriteLine(err.StackTrace);
      }
    }

    private decimal Map(decimal value, decimal fromSource, decimal toSource, decimal fromTarget, decimal toTarget) {
      return Math.Round((value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget);
    }
    public string[] FindJoysticks() {
      systemJoysticks = null;
      try {
        // Find all the GameControl devices that are attached.
        DeviceList gameControllerList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);

        // check that we have at least one device.
        if (gameControllerList.Count > 0) {
          systemJoysticks = new string[gameControllerList.Count];
          int i = 0;
          // loop through the devices.
          foreach (DeviceInstance deviceInstance in gameControllerList) {
            // create a device from this controller so we can retrieve info.
            joystickDevice = new Device(deviceInstance.InstanceGuid);
            joystickDevice.SetCooperativeLevel(hWnd,
                CooperativeLevelFlags.Background |
                CooperativeLevelFlags.NonExclusive);

            systemJoysticks[i] = joystickDevice.DeviceInformation.InstanceName;

            i++;
          }
        }
      } catch (Exception err) {
        Console.WriteLine("FindJoysticks()");
        Console.WriteLine(err.Message);
        Console.WriteLine(err.StackTrace);
      }

      return systemJoysticks;
    }

    /// <summary>
    /// Acquire the named joystick. You can find this joystick through the <see cref="FindJoysticks"/> method.
    /// </summary>
    /// <param name="name">Name of the joystick.</param>
    /// <returns>The success of the connection.</returns>
    public bool AcquireJoystick(string name) {
      try {
        DeviceList gameControllerList = Manager.GetDevices(DeviceClass.GameControl, EnumDevicesFlags.AttachedOnly);
        int i = 0;
        bool found = false;
        // loop through the devices.
        foreach (DeviceInstance deviceInstance in gameControllerList) {
          if (deviceInstance.InstanceName == name) {
            found = true;
            // create a device from this controller so we can retrieve info.
            joystickDevice = new Device(deviceInstance.InstanceGuid);
            joystickDevice.SetCooperativeLevel(hWnd,
                CooperativeLevelFlags.Background |
                CooperativeLevelFlags.NonExclusive);
            break;
          }

          i++;
        }

        if (!found)
          return false;

        // Tell DirectX that this is a Joystick.
        joystickDevice.SetDataFormat(DeviceDataFormat.Joystick);

        // Finally, acquire the device.
        joystickDevice.Acquire();

        // How many axes?
        // Find the capabilities of the joystick
        DeviceCaps cps = joystickDevice.Caps;
        Console.WriteLine("Joystick Axis: " + cps.NumberAxes);
        Console.WriteLine("Joystick Buttons: " + cps.NumberButtons);

        axisCount = cps.NumberAxes;

        UpdateStatus();
      } catch (Exception err) {
        Console.WriteLine("FindJoysticks()");
        Console.WriteLine(err.Message);
        Console.WriteLine(err.StackTrace);
        return false;
      }

      return true;
    }

    /// <summary>
    /// Unaquire a joystick releasing it back to the system.
    /// </summary>
    public void ReleaseJoystick() {
      joystickDevice.Unacquire();
    }

    /// <summary>
    /// Update the properties of button and axis positions.
    /// </summary>
    public void UpdateStatus() {
      int repeat = 20;

      int valueXsum = 0;
      int valueYsum = 0;
      int valueZsum = 0;
      int valueRysum = 0;

      for (int i = 0; i < repeat; i++) {
        Poll();

        valueXsum += state.X;
        valueYsum += state.Y;
        valueZsum += state.Z;
        valueRysum += state.Ry;
      }
      valueXsum /= repeat;
      valueYsum /= repeat;
      valueZsum /= repeat;
      valueRysum /= repeat;

      axisX = valueXsum;
      axisY = valueYsum;
      axisZ = valueZsum;
      axisRy = state.Ry;


      roll = Convert.ToInt32(Map(AxisX, (decimal)rollMin, (decimal)rollMax, -90, 90));
      pitch = Convert.ToInt32(Map(AxisY, (decimal)pitchMin, (decimal)pitchMax, -90, 90));
      throttle = Convert.ToInt32(Map(AxisZ, (decimal)throttleMin, (decimal)throttleMax, 1050, 1900));
      yaw = Convert.ToInt32(Map(AxisRy, (decimal)yawMin, (decimal)rollMax, -180, 180));



      // not using buttons, so don't take the tiny amount of time it takes to get/parse
      byte[] jsButtons = state.GetButtons();
      buttons = new bool[jsButtons.Length];

      int a = 0;
      foreach (byte button in jsButtons) {
        buttons[a] = button >= 128;
        a++;
      }

    }
  }
}
