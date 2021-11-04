using System;
using Reloaded.Mod.Interfaces;
using System.Diagnostics;
using Reloaded.Hooks.Definitions;
using Reloaded.Hooks.Definitions.X64;
using Reloaded.Memory.Sigscan;

namespace DigimonCSLogHook
{
    public class Mod
    {
        private ILogger _logger;
        private IReloadedHooks _hooks;
        private Process _process;
        private IHook<LoadFile> _loadFileHook;

        public Mod(ILogger logger, IReloadedHooks hooks)
        {
            _logger = logger;
            _hooks = hooks;
            _process = Process.GetCurrentProcess();
            using var scanner = new Scanner(_process, _process.MainModule);

            //var result = scanner.CompiledFindPattern("48 8B C4 53 41 56 41 57 48 83 EC 50");
            var result = scanner.CompiledFindPattern("4C 89 44 24 18 48 89 54 24 10 48 89 4C 24 08 55 53 56 57 48 8D 6C 24 D8");

            var functionAddress = result.Offset + (long) _process.MainModule.BaseAddress;
            _logger.WriteLine($"Address: {functionAddress:X}");
            _loadFileHook = _hooks.CreateHook<LoadFile>(LoadFileFunc, functionAddress).Activate();
        }

        private IntPtr LoadFileFunc(IntPtr unk, string filePath, IntPtr unk2)
        {
            _logger.WriteLine($"File: {filePath}");
            return _loadFileHook.OriginalFunction(unk, filePath,unk2);
        }

        [Function(CallingConventions.Microsoft)]
        public delegate IntPtr LoadFile(IntPtr unk, string filePath, IntPtr unk2);
    }
}
