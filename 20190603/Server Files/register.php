<?php

require "config.php";

$username = $_POST["username"];
$password = $_POST["password"];
$checkpwd = $_POST["checkpwd"];

judgeNull($username, "账号");
judgeNull($password, "密码");
judgeNull($checkpwd, "确认密码");

judgeMax($username, "账号", 10);
judgeMax($password, "密码", 16);
judgeMax($checkpwd, "确认密码", 16);

judgeSame($password, $checkpwd);

register($username, $password);







?>