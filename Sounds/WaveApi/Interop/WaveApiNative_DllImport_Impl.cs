using System;
using System.Runtime.InteropServices;

namespace WaveApi.Interop
{
    /// <summary>
    /// 
    /// </summary>
    internal static partial class WaveApiNative
    {
        private const string DllPath = @"lib\WaveApiNative.dll";
        /// <summary>
        /// 
        /// </summary>
        /// <param name="lphwo"></param>
        /// <param name="channels"></param>
        /// <param name="bitsPerSample"></param>
        /// <param name="samplesPerSec"></param>
        /// <param name="formatTag"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall)]
        private extern static uint waveapi_waveOutOpen(out IntPtr lphwo,
            ushort channels, ushort bitsPerSample, long samplesPerSec, 
            ushort formatTag);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="hwo"></param>
        /// <param name="lphdr"></param>
        /// <param name="buffer"></param>
        /// <param name="bufferLength"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall)]
        private extern static uint waveapi_waveOutPrepareHeader(IntPtr hwo,
            ref IntPtr lphdr, byte[] buffer, long bufferLength);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="hwo"></param>
        /// <param name="lpwhdr"></param>
        /// <returns></returns>
        [DllImport(DllPath, CallingConvention = CallingConvention.StdCall)]
        private extern static uint waveapi_waveOutWrite(IntPtr hwo, IntPtr lpwhdr);
    }
}
