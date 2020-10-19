val=$(~/norminette/norminette.rb ~/work/testing_actions/testing_actions/ | grep "Error" | grep -v -c "Error: 42 header not at top of the file")
exit $val