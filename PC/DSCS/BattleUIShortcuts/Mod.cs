using System;
using Reloaded.Mod.Interfaces;
using System.Diagnostics;
using Reloaded.Hooks.Definitions;
using Reloaded.Memory.Sigscan;

namespace BattleUIShortcuts
{
	public class Mod
	{
		private ILogger _logger;
		private IReloadedHooks _hooks;
		private Process _process;
		private IAsmHook _asmHook;

		public Mod(ILogger logger, IReloadedHooks hooks)
		{
			_logger = logger;
			_hooks = hooks;
			_process = Process.GetCurrentProcess();
			using var scanner = new Scanner(_process, _process.MainModule);

			//var result = scanner.CompiledFindPattern("48 8B C4 53 41 56 41 57 48 83 EC 50");
			var result = scanner.CompiledFindPattern("F6 40 08 04 0F 84 DF 01 00 00");

			var injectLocation = result.Offset + (long)_process.MainModule.BaseAddress;
			

			//test byte ptr[rax + 08],04
			//jne "Digimon Story CS.exe.unpacked.exe" + 00171ddb
			//cmp EDI, 0x14
			//je "Digimon Story CS.exe.unpacked.exe" + 00171f3d
			//jmp "Digimon Story CS.exe.unpacked.exe" + 171D5E

			string[] asmCode =
			{   //here we use ecx to hold the jump address temporarily
				$"use64",
				$"test byte [rax + 08],04",
				$"mov rcx, " +String.Format("0x{0:X8}",0x00171ddb+(long)_process.MainModule.BaseAddress).ToString(),
				$"jne jumptorcx",
				$"cmp edi, 0x14",
				$"mov rcx, "+String.Format("0x{0:X8}",0x00171f3d+(long)_process.MainModule.BaseAddress).ToString(),
				$"je jumptorcx",
				$"mov rcx, "+String.Format("0x{0:X8}",0x171D5E+(long)_process.MainModule.BaseAddress).ToString(),
				$"jumptorcx:",
				$"jmp rcx"
			};
#if DEBUG
			_logger.WriteLine($"Inject Location Offset: {result.Offset:X}");
			_logger.WriteLine($"Inject Location: {injectLocation:X}");
			foreach (var asm in asmCode)
			{

				_logger.WriteLine(asm);
			}
#endif
			_asmHook = _hooks.CreateAsmHook(asmCode, injectLocation,Reloaded.Hooks.Definitions.Enums.AsmHookBehaviour.DoNotExecuteOriginal);
			_asmHook.Activate();

		}
	}
}
