# GDB 

## Compilation

- To include debug info, we need to add `-g` flag to `gcc`: `gcc -o program program.c`

## Examining memory

- Print variable: `p <var_name>`
- Print address of variable: `p &<var_name>`

## Stepping through

- Skip to next code line: `next`
- Skip to next instruction: `nexti`
- 


## Layouts

To enter TUI mode, do `C-x C-a`

To toggle between different layouts, do `lay next` and press enter a couple of times