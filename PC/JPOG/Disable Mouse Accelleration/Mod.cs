using Reloaded.Hooks.ReloadedII.Interfaces;
using Reloaded.Memory.Sources;
using Reloaded.Mod.Interfaces;
using System;
using System.Diagnostics;
using System.Runtime;

namespace Disable_Mouse_Accelleration
{
	/// <summary>
	/// Your mod logic goes here.
	/// </summary>
	public class Mod
	{
		private ILogger _logger;
		private IReloadedHooks _hooks;
		private Process _process;
		public Mod(IReloadedHooks hooks, ILogger logger)
		{
			_logger = logger;
			_hooks = hooks;
			_process = Process.GetCurrentProcess();

			foreach(ProcessModule module in _process.Modules)
			{
				if (module.ModuleName == "tguiinterface.dll")
				{
					Memory.Instance.SafeWrite(module.BaseAddress + 0x150C0, 0x000008C2);
					logger.WriteLine("[Disable Mouse Accelleration]: Successfully Patched TGuiInterface.dll!");
					continue;
				}

			}
			
			// TODO: Implement some mod logic    
		}
	}
}