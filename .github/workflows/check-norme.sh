val=$(~/.norminette/norminette.rb ~/work/Codam06_MiniShell/Codam06_MiniShell/ | grep -c "Error")
exit $val