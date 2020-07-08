using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace lab_3_csharp
{
    class Program
    {
        [DllImport("dll_lab_3.dll", EntryPoint = "AddNumbers")]
        public static extern int AddNumbers(int x, int y);

        [DllImport("dll_lab_3.dll", EntryPoint = "GetTime")]
        public static extern IntPtr GetTime();

        [STAThread]
        static void Main(string[] args)
        {
            Console.WriteLine("Sum of 2 and 3 is {0}", AddNumbers(2, 3));
            Console.WriteLine("Current time is {0}", Marshal.PtrToStringAnsi(GetTime()));

            Console.ReadLine();
        }
    }
}
