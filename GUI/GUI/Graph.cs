using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;
using System.Collections;


namespace GUI
{
    class Graph
    {
        private int tickStart;
        private ZedGraphControl zedGraphControl1;
        private List<RollingPointPairList> rollingPointPairList = new List<RollingPointPairList>();
        private GraphPane myPane;
        private Hashtable hashTable = new Hashtable();
        private List<String> namesOfCurves = new List<string>();
        private List<LineItem> curves = new List<LineItem>();

        public void sethashTable(Hashtable hashTable)
        {
            this.hashTable = hashTable;
            
        }

        private Color[] colors = { Color.Red, Color.Yellow, Color.Green, Color.Black, Color.Blue, Color.Brown, Color.DarkBlue, Color.DarkGreen, Color.Aqua };
        private int colorNumber = 8;

       public  Graph(ZedGraphControl zedGraphControl1, string graphTitle, string xAxisTitle, string yAxisTitle, string name1,string name2,string name3)
        {
            this.zedGraphControl1 = zedGraphControl1;
            myPane = zedGraphControl1.GraphPane;
            myPane.Title.Text = graphTitle;
            myPane.XAxis.Title.Text = xAxisTitle;
            myPane.YAxis.Title.Text = yAxisTitle;


            // Save 1200 points.  At 50 ms sample rate, this is one minute
            // The RollingPointPairList is an efficient storage class that always
            // keeps a rolling set of point data without needing to shift any data values
            
           //RollingPointPairList list1 = new RollingPointPairList(70000);
            //RollingPointPairList list2 = new RollingPointPairList(70000);
            //RollingPointPairList list3 = new RollingPointPairList(70000);

              
            // Initially, a curve is added with no data points (list is empty)
            // Color is blue, and there will be no symbol
           
          // LineItem curve1 = myPane.AddCurve(name1, list1, Color.Red, SymbolType.None);
          //  LineItem curve2 = myPane.AddCurve(name2, list2, Color.Blue, SymbolType.None);
          //  LineItem curve3 = myPane.AddCurve(name3, list3, Color.Green, SymbolType.None);
          //  curve1.Line.Width = 1.75F;
          //  curve2.Line.Width = 1.75F;
          //  curve3.Line.Width = 1.75F;
          
           //  Console.WriteLine(zedGraphControl1.GraphPane.CurveList[0].Label.Text);
           // Console.WriteLine(curve1.Label.Text);
            //foreach (String s in hashTable.Keys)
            //{
            //    curves.Add(myPane.AddCurve(s,new RollingPointPairList(70000),Color.Red,SymbolType.None));                  
            //}

           //curve.Line.Fill = new Fill(Color.White, Color.Red, 45F);
            //curve.Line.Width = 2F;

        

            // Just manually control the X axis range so it scrolls continuously
            // instead of discrete step-sized jumps
            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = 50;
            myPane.XAxis.Scale.MinorStep = 0;
            myPane.XAxis.Scale.MajorStep = 3;

            // Scale the axes
            zedGraphControl1.AxisChange();

            // Save the beginning time for reference
            tickStart = Environment.TickCount;

        }

   

        private void checkCurves(Hashtable hash){
            bool found = false;
            bool delete = false;
            LineItem curveToDelete = null;
            foreach (LineItem q in zedGraphControl1.GraphPane.CurveList)
            {
                foreach (String s in hash.Keys)
                {
                    if (q.Label.Text.Equals(s)) {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    //Console.WriteLine(zedGraphControl1.GraphPane.CurveList.IndexOf(q));
                    delete = true;
                    curveToDelete = q;                 
                }
                found = false;
             }
            if (hash.Keys.Count == 0 && zedGraphControl1.GraphPane.CurveList.Count!=0) zedGraphControl1.GraphPane.CurveList.RemoveAt(0);
            if (delete)
            {
                zedGraphControl1.GraphPane.CurveList.Remove(curveToDelete);
                delete = false;
                colorNumber++;
            }

            foreach (String s in hash.Keys)
            {
                foreach (LineItem l in zedGraphControl1.GraphPane.CurveList)
                {
                    if (l.Label.Text.Equals(s))
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    
                    Random r = new Random();
                    int rInt = r.Next(0, colors.Length); //for ints
                    try
                    {
                        LineItem curve = myPane.AddCurve(s, new RollingPointPairList(70000), colors[colorNumber], SymbolType.None);
                        curve.Line.Width = 1.75F;
                        colorNumber--;
                    }
                    catch (Exception e) { MessageBox.Show(e.Message); }
                }
                found = false;
            }

         

        }


  
        public void drawGraph( Hashtable hashT)
        {
            checkCurves(hashT);

            // Make sure that the curvelist has at least one curve
            if (zedGraphControl1.GraphPane.CurveList.Count <= 0)
                return;
            
            // Get the first CurveItem in the graph
            //LineItem curve1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;
            //LineItem curve2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
            //LineItem curve3 = zedGraphControl1.GraphPane.CurveList[2] as LineItem;
            //if (curve1 == null || curve3 == null || curve2 == null)
            //    return;

            List<LineItem> inGraphCurve = new List<LineItem>();
            foreach (LineItem s in zedGraphControl1.GraphPane.CurveList)
            {
                inGraphCurve.Add(s as LineItem);
            }
            if (inGraphCurve.Count == 0) return;
            
            



            //// Get the PointPairList
            //IPointListEdit list1 = curve1.Points as IPointListEdit;    
            //IPointListEdit list2 = curve2.Points as IPointListEdit;
            //IPointListEdit list3 = curve3.Points as IPointListEdit;
            //if this is null, it means the reference at curve.points does not
            // support IPointListEdit, so we won't be able to modify it
            //if (list1 == null || list2 == null || list3 == null)
            //    return;

            List<IPointListEdit> list = new List<IPointListEdit>();
            foreach (LineItem s in inGraphCurve)
            {
                list.Add(s.Points as IPointListEdit);
            }
            if (list.Count == 0) return;

            
          

            // Time is measured in seconds
            double time = (Environment.TickCount - tickStart) / 1000.0;
            
            // 3 seconds per cycle
            foreach (String s in hashT.Keys)
                {            
                 for (int i = 0; i < list.Count; i++)
                      {
                          if (inGraphCurve[i].Label.Text.Equals(s)) list[i].Add(time, Convert.ToDouble(hashT[s]));
                      }
             
            }
            //list2.Add(time, value2);
            //list3.Add(time, value3);

            //foreach (IPointListEdit s in list)
            //{
            //    s.Add(time,value1);
            //}

            //neeed to finish 





            // Keep the X scale at a rolling 30 second interval, with one
            // major step between the max X value and the end of the axis
            Scale xScale = zedGraphControl1.GraphPane.XAxis.Scale;
            if (time > xScale.Max - xScale.MajorStep)
            {
                xScale.Max = time + xScale.MajorStep;
                xScale.Min = xScale.Max - 10.0;
            }

            // Make sure the Y axis is rescaled to accommodate actual data
            zedGraphControl1.AxisChange();
            // Force a redraw
            zedGraphControl1.Invalidate();
            zedGraphControl1.IsShowPointValues = true;
            zedGraphControl1.PointValueFormat = "0.000";
            zedGraphControl1.PointDateFormat = "d";
        }
    }
}
