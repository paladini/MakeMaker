![MakeMaker - Generate makefiles quickly!](documentation/logo.png)<br/>
Generate makefiles quickly with MakeMaker.

# Installation

1. Download the [latest version of MakeMaker](https://github.com/paladini/MakeMaker/archive/master.zip).
2. Extract it anywhere you want.
3. Run `sudo make install` on the MakeMaker folder.
4. Done!

Now you can use `mm` to run MakeMaker. Please, check our current specification below.

# Current specification:

	## Create target
	mm add <target>
		
	## Add command to target *(also create the target if it doesn't exist)*
	mm add <target> <command>

	Where <command> is
		<compiler> <filename.ext, filename2.ext, ...> <flags>
		
	## Rename target
	mm edit <oldTargetName> <newTargetName>

	## Replace command from specific target.
	mm edit <target>:<number_line> <command>

	Where <command> is just
		<compiler> <filename.ext, filename2.ext, ...> <flags>

	## Delete target
	mm remove <target>

	## Delete command from specific target.
	mm remove <target>:<number_line>
