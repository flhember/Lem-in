# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 14:35:12 by chcoutur          #+#    #+#              #
#    Updated: 2020/02/18 18:06:25 by chcoutur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

################################
red=$'\e[1;31m'
grn=$'\e[1;32m'
yel=$'\e[1;33m'
blu=$'\e[1;34m'
mag=$'\e[1;35m'
cyn=$'\e[1;36m'
end=$'\e[0m'
###############################


x=0
real=0
yours=0
clear

function big
{

	type="big"
	echo "-> You selected big maps"
	sleep 1
	clear
	while [ $x -le $round ]
	do
		echo "On ${mag}$type${end} maps | test ${blu}$x${end}/$round"
		real=$(./maps/generator --$type > map_check && tail -n1 map_check | sed 's/.*\(...\)/\1/')
		printf "\n${yel}real${end}\t[$real]"
		yours=$(./lem-in < map_check | grep "L" | wc -l | cut -c6-)
		printf "\n${grn}your${end}\t[$yours]\n"
		x=$(( $x + 1))
		sleep 1
		clear
	done
}

function big_superposition
{

	type="big-superposition"
	echo "-> You selected big-superposition maps"
	sleep 1
	clear
	while [ $x -le $round ]
	do
		echo "On ${mag}$type${end} maps | test ${blu}$x${end}/$round"
		real=$(./maps/generator --$type > map_check && tail -n1 map_check | sed 's/.*\(...\)/\1/')
		printf "\n${yel}real${end}\t[$real]"
		yours=$(./lem-in < map_check | grep "L" | wc -l | cut -c6-)
		printf "\n${grn}your${end}\t[$yours]\n"
		x=$(( $x + 1))
		sleep 1
		clear
	done
}

function flow_one
{

	type="flow-one"
	echo "-> You selected flow-one maps"
	sleep 1
	clear
	while [ $x -le $round ]
	do
		echo "On ${mag}$type${end} maps | test ${blu}$x${end}/$round"
		real=$(./maps/generator --$type > map_check && tail -n1 map_check | sed 's/.*\(...\)/\1/')
		printf "\n${yel}real${end}\t[$real]"
		yours=$(./lem-in < map_check | grep "L" | wc -l | cut -c6-)
		printf "\n${grn}your${end}\t[$yours]\n"
		x=$(( $x + 1))
		sleep 1
		clear
	done
}

function flow_ten
{

	type="flow-ten"
	echo "-> You selected flow-ten maps"
	sleep 1
	clear
	while [ $x -le $round ]
	do
		echo "On ${mag}$type${end} maps | test ${blu}$x${end}/$round"
		real=$(./maps/generator --$type > map_check && tail -n1 map_check | sed 's/.*\(...\)/\1/')
		printf "\n${yel}real${end}\t[$real]"
		yours=$(./lem-in < map_check | grep "L" | wc -l | cut -c6-)
		printf "\n${grn}your${end}\t[$yours]\n"
		x=$(( $x + 1))
		sleep 1
		clear
	done
}

function flow_thousand
{

	type="flow-thousand"
	echo "-> You selected flow-thousand maps"
	sleep 1
	clear
	while [ $x -le $round ]
	do
		echo "On ${mag}$type${end} maps | test ${blu}$x${end}/$round"
		real=$(./maps/generator --$type > map_check && tail -n1 map_check | sed 's/.*\(...\)/\1/')
		printf "\n${yel}real${end}\t[$real]"
		yours=$(./lem-in < map_check | grep "L" | wc -l | cut -c6-)
		printf "\n${grn}your${end}\t[$yours]\n"
		x=$(( $x + 1))
		sleep 1
		clear
	done
}

function do_exit
{
    echo "-> Exit the script"
    exit
}

# Function that displays the menu
function display_menu
{
    # Declare an array containing the actions to do
    local -a MY_ACTIONS
	printf "${yel}Which kind of maps on ${end}[${blu}$round${end}] ${yel}rounds ?${end}\n\n"
	MY_ACTIONS[1]="big"
	MY_ACTIONS[2]="big_superposition"
	MY_ACTIONS[3]="flow_one"
	MY_ACTIONS[4]="flow_ten"
	MY_ACTIONS[5]="flow_thousand"
	MY_ACTIONS[6]="do_exit"

	# Display items
	local -i I=1
	echo "#########################"
	while [ $I -le ${#MY_ACTIONS[@]} ]
	do
		echo "$I) ${MY_ACTIONS[$I]}"
		(( I += 1 ))
	done

	# Read keyboard silently, one character at a time, 
	# and save the value in $SELECTION
	local USR_CHOICE
	read -s -n1 USR_CHOICE

	# Convert the ascii value of $SELECTION into a numeric index
	local ORD_VALUE=$(LC_CTYPE=C printf '%d' "'$USR_CHOICE")
	(( ORD_VALUE -= 48 ))

	# Check if the index is valid
	if [ $ORD_VALUE -gt 0 -a $ORD_VALUE -le ${#MY_ACTIONS[@]} ]
	then
		# If yes, evaluate the action and exit the function
		eval ${MY_ACTIONS[${ORD_VALUE}]}
		return
	fi

	# If not, call display_menu one more time
	echo "-> INVALID SELECTION"
	display_menu
}

# Call the menu

printf "How many rounds of check ? : "
read round
clear
display_menu
