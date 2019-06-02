<?php

require "config.php";

$user_id = $_POST["user_id"];
$name = $_POST["name"];
$abbr = $_POST["abbr"];
$teacher = $_POST["teacher"];
$location = $_POST["location"];
$week = $_POST["week"];
$day = $_POST["day"];
$start = $_POST["start"];
$end = $_POST["end"];

judgeNull($user_id, "user_id");
judgeNull($name, "name");
judgeNull($teacher, "teacher");
judgeNull($location, "location");
judgeNull($week, "week");
judgeNull($day, "day");
judgeNull($start, "start");
judgeNull($end, "end");

addCourse($user_id, $name, $abbr, $teacher, $location, $week, $day, $start, $end);














?>