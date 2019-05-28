<?php

require "config.php";

$username = $_POST["username"];
$password = $_POST["password"];

judgeNull($username, "账号");
judgeNull($password, "密码");

login($username, $password);











?>