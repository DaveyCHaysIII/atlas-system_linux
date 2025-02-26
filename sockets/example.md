[copy_files] Filed copied: check_server.bash
[exec_bash_compare] Command to run:
chmod +x check_server.bash
su student_jail -c 'timeout 30 bash -c '"'"'chmod +x check_server.bash'"'"''
[exec_bash_compare] Return code: 0
[exec_bash_compare] Student stdout:
[exec_bash_compare] Student stdout length: 0
[exec_bash_compare] Student stderr:
[exec_bash_compare] Student stderr length: 0
[exec_bash_compare] Desired stdout:
[exec_bash_compare] Desired stdout length: 0
[exec_bash_compare] Command to run:
./check_server.bash ./todo_api_4
su student_jail -c 'timeout 30 bash -c '"'"'./check_server.bash ./todo_api_4'"'"''
[exec_bash_compare] Return code: 52
[exec_bash_compare] Student stdout:
[exec_bash_compare] Student stdout length: 0
[exec_bash_compare] Student stderr:
[exec_bash_compare] Student stderr length: 0
[exec_bash_compare] Desired stdout:
[exec_bash_compare] Desired stdout length: 0
[compare] Command to run:
cat curl_output
su student_jail -c 'timeout 30 bash -c '"'"'cat curl_output'"'"''
[compare] Return code: 0

[compare] Student stdout:
HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":0,"title":"Holberton","description":"School"}HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":0,"title":"Holberton","description":"School"}HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":0,"title":"School","description":"Holberton"}

[compare] Student stdout length: 381
[compare] Student stderr:
[compare] Student stderr length: 0

[compare] Desired stdout:
HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":0,"title":"Holberton","description":"School"}HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":1,"title":"Holberton","description":"School"}HTTP/1.1 201 Created
Content-Length: 51
Content-Type: application/json
{"id":2,"title":"Holberton","description":"School"}HTTP/1.1 422 Unprocessable Entity
HTTP/1.1 404 Not Found

[compare] Desired stdout length: 444
