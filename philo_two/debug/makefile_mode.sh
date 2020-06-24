#!/bin/zsh

NORMAL=$(tput sgr0)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)


cat Makefile > old_makefile.txt 2> /dev/null
if [[ $(cat old_makefile.txt) == "" ]]
then
	echo "❌ ${RED}Vous devez appeller ce script sur le dossier ou se site votre Makefile${NORMAL}"
	rm -f old_makefile.txt
	exit
fi

if [ $1 = "linux" ]
then
	MODE="LINUX"
	sed -i "s/lncurses/pthread/g" Makefile
	# sed -i '' "s/lncurses/pthread/g" Makefile
else
	MODE="NORMAL"
	sed -i "s/pthread/lncurses/g" Makefile
	# sed -i '' "s/pthread/lncurses/g" Makefile
fi

clear
echo "✅ ${GREEN} ${MODE} MODE SET${NORMAL}"
rm -f old_makefile.txt