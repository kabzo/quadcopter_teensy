Quadcopter
==========
Developing complet quadcopter flight control-board.

h3> Components </h3>
<ul>
    <li>Teensy 3.1: more advanced and powerfull than arduino</li>
    <li>MPU 9150: 9-axis MotionTracking device</li>
    <li>Bluetooth: wireless communication between board and computer (or possibly android device)</li>
    <li>Diods: Visual feedback of the boards state</li>
    <li>RC receiver: User control of quadcopter</li>
    <li>Quadcopter:
        <ul>
            <li>Motors: SunnySky x2212</li>
            <li>ESC: HobbyKing 20A</li>
            <li>Prop: 8045</li>
        </ul>
</ul>

<h3> Communication </h3>
For communication between drone and <a href="http://qgroundcontrol.org/">GCS</a> was used <a href="http://qgroundcontrol.org/mavlink/start">MAVLINK</a> protocol (also used in the
<a href="https://pixhawk.org/choice"> PIXHAWK</a> and <a href="http://ardupilot.com/"> APM</a>).
This is very effective and lightweight protocol which covers transfer of the most important flight informations."
<h3>Specifications</h3>
<ul>
    <li>Flight Time: around 15-20min min on 4000mAh lipo</li>
    <li>Stability: Video on youtube is old and the newest software update and tuned PID constants results to very stable
        flight
    </li>
    <li>Controlling: Either through classic RC controller or pc joystick</li>
</ul>
