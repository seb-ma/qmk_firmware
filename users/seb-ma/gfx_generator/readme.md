# Helpers to generate sprites animations

This folder includes only files that are not part of the firmware.
It contains input pictures of animations and generators of compressed versions of animations.

## Core generator

The file [generator.c](generator.c) is the core of the generator.
It gives a list of non common characters related to other bitmaps. This way, a bitmap may be stored only for parts blacks or for parts that changes from a previous sprite.

- It takes a bitmap to output and other bitmaps to compare with
- It generates 3 `C` arrays
  - index (in delta related to previous) of differences in bitmap related to others
  - size of difference for each index (related to index array)
  - values of char in bitmaps (related to index array)
- Arrays are output to stdout

## Bongocat

The file [gen_bongocat.c](gen_bongocat.c) is the generator configured for the Bongocat animation.
The folder [in_bongocat](in_bongocat) contains svg of bongocat and [bitmaps](in_bongocat/bitmaps.h) used by generator.

Compilation and execution in one shot:

```bash
gcc generator.c gen_bongocat.c -o gen_bongocat && .\gen_bongocat
```

## Oneko

The file [gen_oneko.c](gen_oneko.c) is the generator configured for the Oneko animation.
The folder [in_oneko](in_oneko) contains [bitmaps](in_oneko/bitmaps.h) used by generator.

Compilation and execution in one shot:

```bash
gcc generator.c gen_bongocat.c -o gen_oneko && .\gen_oneko
```
