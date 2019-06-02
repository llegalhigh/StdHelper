<?php

require "config.php";

$user_id = $_POST["user_id"];

judgeNull($user_id, "user_id");

showCourse($user_id);














?>