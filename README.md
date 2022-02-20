# split4sync

Split large files into multiple parts to prevent synchronization failures due to file size limitations

I hope it's useless. (I made it because I don't know how to join splitted files by `GNU Parallel`)

## Installation

```bash
git clone https://github.com/mjy9088/split4sync.git
cd split4sync
git checkout v1.0

mkdir build
cd build
cmake ..

make
make test
sudo make install
```

## Usage

```text
usage :
    s4s help - this
    s4s join filename - join spllitted files into stdout
    s4s split filename size - split stdin to multiple files
```

### split

```bash
make_some_large_output | gzip | s4s split 1048576 test
```

### join

```bash
s4s join test | gzip -d > original_large_output_file
```
