using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ActiveXCPP2Lib;            //не забудьте добавить строки подключения
using AxActiveXCPP2Lib;


namespace lab_2
{
    public partial class Form1 : Form
    {
        static float square;
        public Form1()
        {
            InitializeComponent();
            axActiveXCPP21.EventHandlerTest += new AxActiveXCPP2Lib._DActiveXCPP2Events_EventHandlerTestEventHandler(axActiveXCPP21_EventHandlerTest);
        }

       private void axActiveXCPP21_EventHandlerTest(object sender, _DActiveXCPP2Events_EventHandlerTestEvent e)
        {
            int radius = e.radius;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            square = axActiveXCPP21.TestMyMethod((int)numericUpDown1.Value);
            MessageBox.Show("Square of circle = " + square);
        }
    }
}
