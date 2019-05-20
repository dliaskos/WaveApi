using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SoundWaves
{
    class Program
    {
        static void Main(string[] args)
        {
            var player = new WaveApi.WaveApi();

            player.Play("C:\\devel\\resources\\carlin_boring.wav");

            Console.ReadKey();
        }
    }
}
