" echo "The val of 'shell' is" &shell

color default

" Boolean Settings ----------------------------

set shiftround  " set rounding with >> to col multiply of shitfwidth
set number " row numbers
set ruler " right corner numbers 
set cursorline " if we want - underline 
set autoindent " automatical indentation
set noeb " no error beep

" Value Settings ------------------------------

set shiftwidth=4	" rounding with > (indenting)
set tabstop=4 	" n of spaces in tab
set timeoutlen=50 " time between keystrokes

" Mappings ------------------------------------

" set this as a prefix for commands
let mapleader = ","

" move whole line 1 down
nnoremap - ddp 

" move whole line 1 up
nnoremap _ kddpk

" convert current word into uppercase in insert mode
inoremap <leader>u <esc>viwUea

" convert current word into uppercase in normal mode
nnoremap <leader>u viwU

" compile current file to a.out binary
noremap <leader>g <esc>:w<CR>:!g++ % -std=c++11 -Wextra -Wall -O3<CR>
noremap <leader>e <esc>:!./a.out<CR>
noremap <leader>t <esc>:!./a.out < example.in<CR>

" run python script
noremap <leader>r <esc>:w<CR>:!python3 %<CR>
