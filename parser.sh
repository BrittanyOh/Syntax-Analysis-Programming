#!/bin/bash

function parser(){
  gcc -o run ../syntax_analysis.c
  ./run $1
}
