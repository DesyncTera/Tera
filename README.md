A simple PowerSwitcher that switches the currect power mode from Balanced to Power Saver. Of course this can go back and fourth, this is just for people who don't really do anything such as gaming/modeling and have a high/mid end PC, it just saves time from going all the way into control panel and searching for the power mode each time. 

Note: This does not modify the individual settings of each power mode; it only switches between them. To adjust the settings for each mode and manage your PC's resource usage, you can customize them through the Control Panel. Control panel > HardWare And Sounds > Power Options > Change Plan Settings > Customize each to your liking. I personaly put the power saver on the lowest possible due to high electrical bills (this is mostly on when I'm watching a movie/YouTube). 



https://www.virustotal.com/gui/file/951611cc1586d9282de03a4b7e84d4a6bdc629568dad2934f2c73893435d0a48/detection 

The reason behind a shellcode runner detection is because well it is a shellcode runner, I used the ShellExecute function to execute some commands via the cmd.exe, this puts the powercfg into use to change the power modes. 

First example in the code:

ShellExecute(NULL, L"open", L"cmd.exe", L"/C powercfg /setactive SCHEME_BALANCED", NULL, SW_HIDE);       

Second example:

ShellExecute(NULL, L"open", L"cmd.exe", L"/C powercfg /setactive SCHEME_MAX", NULL, SW_HIDE);

These I believe are the only times ShellExecute is used, it's well known for security vendors to flag this as malware because it acts like it. 
