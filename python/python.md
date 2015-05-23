---
layout: default
---
#Python memo
 
##Installation
Add python search path
```
import sys
sys.path.append('/www/python/')
```

change default installation library. Put the following lines in the ~/.pydistutils.cfg  file
```
[install]
install-lib=/home/bernardo/lianl0/python
install-purelib=lib
install-platlib=lib.$PLAT
install-scripts=scripts
install-headers=python/include
install-data=data
```
install with:
easy_install pandas

Or using the following command

```
module load python-epd
cd pandas
python setup.py install
```
##Interactive plotting
Unable to access the X Display, is DISPLAY set properly?
```
import matplotlib
matplotlib.use('Agg') # Must be before importing matplotlib.pyplot or pylab!
import matplotlib.pyplot as plt
import pandas as pd
fig = plt.figure()
plt.plot(range(10))
fig.savefig('temp.png')
```
If you want this to be the default behavior, you can modify your matplotlibrc file to use the Agg backend by default. 
```
file is in .config/matplotlib/matplotlibrc
find -name matplotlibrc
```
open that file, put this line in the file backend: agg

Install packages locally
Go to source folder 
```
python setup.py install --home=~/python
```
##Use modules
```
sudo easy_install pandas
or pip install pandas
```

```
import pandas
pandas.Series([4, 7, -5, 3])
```
or use the following command
from pandas import *
or from pandas import Series
```
Series([4, 7, -5, 3])
```
Sometimes, when you try to import pandas, it will report ImportError: cannot import name hashtable. This might be due to the fact your current working directory contains pandas. If you change the working directory, and import pandas from there, you will be able to import it.</p>


If one method does not correctly install your package, you can try another method

### post_url  File handles.html
## Packages  
### [rpy2](post_url ./rpy2.html)

##Slicing and Dicing
 [slicing and Dicing](post_url slicing and dicing.html)