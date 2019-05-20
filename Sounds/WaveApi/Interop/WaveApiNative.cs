using System;

namespace WaveApi.Interop
{
    internal static partial class WaveApiNative
    {
        /// <summary>
        /// Open WAVE_MAPPER for playback and return the device handle
        /// </summary>
        /// <param name="lphwo"></param>
        /// <param name="channels"></param>
        /// <param name="bitsPerSample"></param>
        /// <param name="samplesPerSec"></param>
        /// <param name="formatTag"></param>
        /// <returns></returns>
        public static uint WaveOutOpen(out IntPtr lphwo, ushort channels,
            ushort bitsPerSample, long samplesPerSec, ushort formatTag)
        {
            return waveapi_waveOutOpen(out lphwo, channels,
                bitsPerSample, samplesPerSec, formatTag);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="hwo"></param>
        /// <param name="lpwhdr"></param>
        /// <param name="buffer"></param>
        /// <param name="bufferLength"></param>
        /// <returns></returns>
        public static uint WaveOutPrepareHeader(IntPtr hwo, ref IntPtr lpwhdr,
            byte[] buffer, long bufferLength)
        {
            return waveapi_waveOutPrepareHeader(hwo, ref lpwhdr,
                buffer, bufferLength);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="hwo"></param>
        /// <param name="lpwhdr"></param>
        /// <returns></returns>
        public static uint WaveOutWrite(IntPtr hwo, IntPtr lpwhdr)
        {
            return waveapi_waveOutWrite(hwo, lpwhdr);
        }
    }
}
