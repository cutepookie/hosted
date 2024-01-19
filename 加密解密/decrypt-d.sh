#!/bin/bash

decrypt()
{
	for file in $1/*
	do
	    if test -f $file
	    then
	        cfname=`basename -s .cb $file`
	        out=${cfname}.xml
	        ./decrypt_tools $file $1/$out 1
	    fi

	    if test -d $file 
	    then
	    	cfname=`basename -s .cb $file`
	        decrypt $file
		fi
	done
}

encrypt()
{
	for file in $1/*
	do
	    if test -f $file
	    then
	        cfname=`basename -s .xml $file`
	        out=${cfname}.cb
	        ./decrypt_tools $file $1/$out 0
	    fi

	    if test -d $file 
	    then
	    	cfname=`basename -s .cb $file`
	        encrypt $file
		fi
	done
}

decrypt "./config-game"