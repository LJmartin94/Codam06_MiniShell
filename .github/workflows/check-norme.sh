val=$(~/norminette/norminette.rb ~/work/Codam06_MiniShell/Codam06_MiniShell/ | grep "Error" | grep -v -c "Error: 42 header not at top of the file")
exit $val