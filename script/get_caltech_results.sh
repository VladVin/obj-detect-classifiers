#!/bin/bash

python download_caltech_results.py

for fname in /home/vlad/tools/code3.2.1/data-INRIA/res/*.zip; do
	unzip $fname -d /home/vlad/tools/code3.2.1/data-INRIA/res/
	rm -R $fname
done