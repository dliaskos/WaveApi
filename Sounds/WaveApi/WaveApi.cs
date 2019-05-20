using System;
using System.IO;

namespace WaveApi
{
    /// <summary>
    /// 
    /// </summary>
    public class WaveApi : IWaveApi, IDisposable
    {
        /// <summary>
        /// Device handle for playback
        /// </summary>
        private readonly IntPtr waveOutHandle_;

        /// <summary>
        /// 
        /// </summary>
        public WaveApi()
        {
            var result = Interop.WaveApiNative.WaveOutOpen(
                out var hwo, 1, 8, 11000, 1);

            if (result != 0) {
                throw new Exception("Could not open WAVE_MAPPER");
            }

            waveOutHandle_ = hwo;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="filePath"></param>
        public void Play(string filePath)
        {
            var lpwhdr = IntPtr.Zero;
            var buffer = File.ReadAllBytes(filePath);

            var result = Interop.WaveApiNative.WaveOutPrepareHeader(
                waveOutHandle_, ref lpwhdr, buffer, buffer.LongLength);

            if (result != 0) {
                throw new Exception("Error preparing playback header");
            }

            result = Interop.WaveApiNative.WaveOutWrite(waveOutHandle_, lpwhdr);

            if (result != 0) {
                throw new Exception("Error writing to WAVE_MAPPER device");
            }

            // TODO: call wave api unprepare header function
            // TODO: free lpwhdr
        }

        #region IDisposable Support
        private bool disposedValue = false;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue) {
                if (disposing) {
                    // TODO: dispose managed state (managed objects).
                }

                // close device handle

                disposedValue = true;
            }
        }

        ~WaveApi()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion
    }
}
