# nm-otool

This school project consists of recoding `nm` - without parameters - and `otool` - as in the `otool -t` - commands.

# Installation

### Requirements

- `gcc`

## Usage

### ft_nm

```
Usage: ft_nm [file ...]
```

### ft_otool

```
Usage: ft_otool [file ...]
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License

[MIT](https://github.com/moannuo/nm-otool/blob/master/LICENSE)

# How does it work?

`nm` is used in UNIX system to examine binary files.

## Example

```
$> nm test.o
0000000a T global_function
00000025 T global_function2
00000004 C global_var
00000000 D global_var_init
00000004 b local_static_var.1255
00000008 d local_static_var_init.1256
0000003b T main
00000036 T non_mangled_function
00000000 t static_function
00000000 b static_var
00000004 d static_var_init
```

The first column is the _symbol value_, the second is the _type_ and the last one is the _name_.

## Ressources

- [Open Source implementation](https://opensource.apple.com/source/cctools/cctools-758/misc/nm.c) by Apple,
- [Parsing Mach-O files]c(https://lowlevelbits.org/parsing-mach-o-files/) tutorial