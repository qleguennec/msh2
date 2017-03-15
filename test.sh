#! /bin/bash

TESTDIR="test"
MSH="../minishell"
ENV="/usr/bin/env"
A="a.out"
B="b.out"

if [ "$#" -ne 1 ]; then
	echo "usage: ./test.sh [env]"
	exit 1
fi

if [ ! -d "$TESTDIR" ]; then
	mkdir "$TESTDIR"
fi

cd $TESTDIR

function test_env()
{
	$ENV | grep -v '^_=' | sort > $A
	echo env | $MSH | grep -v '^_=' | sort > $B
	if cmp -s $A $B; then
		echo "basic test ok"
	else
		vim -d a.out b.out
	fi
}

case "$1" in
	env)
		test_env
		;;
	*)
		echo "unknown option $1"
		exit 2
		;;
esac
