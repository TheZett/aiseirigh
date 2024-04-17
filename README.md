Aiseirigh v0.1 – by Davee  
(Aiseirigh Documentation – by The Zett)

----------------------------------------------------------------------------------------------------------------------------------------------------------------

Requirements:
- a Memory Stick Pro Duo (PSP) or Memory Stick Micro (PSPgo) with sufficient IPL sector space
- a physical BaryonSweeper (mandatory for PSP 3000 03g, 3000 04g, 3000 07g, 3000 09g, PSPgo and PSP E1000; also works for PSP 1000 and 2000)
	- alternatively a classic Pandory battery (only for PSP 1000 and 2000, including 2000 88v3!)
- a software that can interact with the BaryonSweeper, such as pySweeper
	- pySweeper requires Python3 to be properly installed and set up, alongside the following pip packages: "pycryptodome", "tk", "pyserial" and "requests"
- The 6.61 firmware updater files for regular PSPs or the PSPgo (matching your model)
- the Aiseirigh unbricker IPL file
- a way of injecting the Aiseirigh IPL file into the memory stick (e.g. Rains IPL Tool via PC or PSP-Tool via PSP)
- a little bit of reading comprehension :P

----------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------

First Steps (Rains):
- connect your PSP memory stick to your computer
- Opens RainsIPLMStool
- Make sure that RainsIPLMStool properly detected your PSP or Memory Stick (Target Drive)
- Make sure that the "Task to Execute" is set to 'Inject IPL to Memory Stick'
- Click on the "IPL" drop-down window in the top-right corner and select "Load IPL from File"
- Choose the aiseirigh.ipl file
- Click the big "Execute Selected" button

If everything went as planned, it should say "IPL successfully written to MS." in its left box. Proceed to Section Two.
If everything went as planned, be sure to skip the PSPTool section, as it is not required if Rains did the job.

But if it says "insufficient sector space memory, failed to write IPL", then you'll need to either try a different memory stick (e.g. an 8GB SanDisk Memory Stick) or you can re-format your Memory Stick with PSPTool (next section).

----------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------


Alternative First Steps (PSPTool):
- Rename the "aiseirigh.ipl" file to "ipl.bin"
- Connect your PSP memory stick to your computer
- Copy the ipl.bin file to the root of your PSP's memory stick
- Copy the PSP folder, that is contained in the PSPTool-1.00.zip file, to your PSP's memory stick
- Disconnect your PSP memory stick from your computer
- Reinsert the memory stick into the PSP
- Launch the PSPTool Homebrew on your PSP (this requires the PSP to be running a Custom Firmware and plugins to be disabled)
- Choose Memory Stick Options
- Choose Inject IPL to Memory Stick
- Choose Inject IPL from ms0:/ipl.bin

If everything went as planned, then the IPL should be injected into the Memory Stick's sector space. Proceed to Section Two.

But if injecting the IPL failed, go back to PSPTool's Memory Stick Options and choose the "Format Memory Stick" option. This will re-format your Memory Stick and should fix the sector space being too small.
AFTERWARDS YOU WILL HAVE TO COPY ALL THE FILES ONTO THE MEMORY STICK ONCE AGAIN! Next, go back to either of the "First Steps" sections and inject the IPL file.

----------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------

Section Two (Preparing the Memory Stick):
- Connect your PSP memory stick to your computer
- Copy either the 661.PBP or the 661GO.PBP to the root of your PSP's memory stick (PSPgo uses 661GO.PBP, every other PSP uses 661.PBP)
- Disconnect your PSP memory stick from your computer
- Reinsert the memory stick into the PSP

----------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------


Section Three (Using pySweeper and the BaryonSweeper):
- Connect your physical BaryonSweeper to your computer via USB
- Open the pySweeper.py file (this requires Python3 and the above mentioned pip packages to be properly set up!)
- Make sure that "Service Mode" is the selected mode
- Choose the correct COM Port, e.g. COM4 (the one that pySweeper has detected your BaryonSweeper on)
- Press "Start Service", pySweeper should now be sending FFFFFFFF to the BaryonSweeper
- Plug the other end of the BaryonSweeper into your PSP or PSPgo
- If the PSP does not automatically turn on, use the power switch to manually turn it on.
(Only for PSP E1000: you have to hold L+R+LEFT+Circle prior to turning it on, as described here: https://www.psdevwiki.com/psp/Button_Combos)

If done properly, the BaryonSweeper should now show some crypto stuff in its Protocol Monitor box.
Then the PSP should automatically turn on and boot into Aiseirigh! Congratulations!
Once Aiseirigh has booted, you can disconnect the BaryonSweeper from your PSP. You might want to have the external charges connected to your PSP while it is running Aiseirigh.

----------------------------------------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------------------------------------

Section Four (Using Aiseirigh):
- Press X to install the 6.61 firmware
- You can press L to toggle between simplified and advanced mode before and during the installation, use whichever one you like best :)
- Once the installation is done, simply press X to turn off the PSP.
- If the PSP does not automatically reboot, use the power switch to boot manually.

Thats it, your PSP should now be running firmware 6.61 and be fully unbricked, if it previously happened to be fully bricked!
