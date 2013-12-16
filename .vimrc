map <Leader>m :call VimuxRunCommand("clear; make run")<CR>
let g:syntastic_cpp_compiler = 'clang'
let g:syntastic_cpp_compiler_options = ' -std=c++11 -stdlib=libc++'
