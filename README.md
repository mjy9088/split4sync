# split4sync
Split large files into multiple parts to prevent synchronization failures due to file size limitations

I hope it's useless. (I made it because I don't know how to join splitted files by `GNU Parallel`)



## Installation

```bash
git clone https://github.com/mjy9088/split4sync.git
mkdir split4sync_build
cd split4sync_build
cmake ../split4sync
make
make install
```

