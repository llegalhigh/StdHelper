<?php
header('Access-Control-Allow-Origin:*');
header('Content-Type: application/json');

$SERVER = "localhost";
$USERNAME = "root";
$PASSWORD = "";//密码示例
$DB = "qt";

function getResult($errcode, $msg, $data){
    $result = [
        "errcode" => $errcode,
        "msg" => $msg,
        "data" => $data
    ];
    echo json_encode($result);
    exit;
}

$con = new mysqli($SERVER,$USERNAME,$PASSWORD,$DB);
if($con->connect_error){
    getResult(-1, "connect database wrong", "");
}
$con->query("SET NAMES utf8mb4");

function judgeNull($content, $information){
    if($content == null){
        getResult(-1, $information." can't be null", "");
    }
}

function judgeMax($content, $information, $number){
    if(iconv_strlen($content,"utf-8") > $number){
        getResult(-1, $information." can't exceed ".$number."characters", "");
    }
}

function login($username, $password){
    global $con;
    $sql = "SELECT count(`id`) as `num` FROM `userInformation` WHERE `username`=? AND `password`=?";

    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare wrong", "login");
    }

    if(!$stmt->bind_param("ss", $username, $password)){
        getResult(-1, "bind_param wrong", "login");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute wrong", "login");
    }

    $res = $stmt->get_result();
    $row = $res->fetch_array();
    if($row["num"] == 0){
        getResult(-1, "username or password wrong", "login");
    }

    getResult(1, "Login successfully", "");
}

function judgeSame($password, $checkpwd){
    if($password != $checkpwd){
        getResult(-1, "Two passwords are different", "judgeSame");
    }
}

function register($username, $password){
    global $con;
    $sql = "SELECT count(`id`) as `num` FROM `userInformation` WHERE `username`=?";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare wrong", "register1");
    }

    if(!$stmt->bind_param("s", $username)){
        getResult(-1, "bind_param wrong", "register1");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute wrong", "register1");
    }

    $res = $stmt->get_result();
    $row = $res->fetch_array();
    if($row["num"] != 0){
        getResult(-1, "Username already existed", "register");
    }

    $sql = "INSERT INTO `userInformation`(`username`,`password`) VALUES (?,?)";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare wrong", "register2");
    }

    if(!$stmt->bind_param("ss", $username, $password)){
        getResult(-1, "bind_param wrong", "register2");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute wrong", "register2");
    }

    getResult(1, "Register successfully", "");
}


function addCourse($user_id, $name, $abbr, $teacher, $location, $week, $day, $start, $end){
    global $con;
    $sql = "INSERT INTO `courselist`(`user_id`,`name`,`abbr`,`teacher`,`location`,`week`,`day`,`start`,`end`) VALUES (?,?,?,?,?,?,?,?,?)";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare wrong", "addCourse");
    }

    if(!$stmt->bind_param("isssssiii", $user_id, $name, $abbr, $teacher, $location, $week, $day, $start, $end)){
        getResult(-1, "bind_param wrong", "addCourse");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute wrong", "addCourse");
    }

    getResult(1, "Add course successfully", "");
}

function showCourse($user_id){
    global $con;
    $sql = "SELECT * FROM `courselist` WHERE `user_id`=?";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare wrong", "showCourse");
    }

    if(!$stmt->bind_param("i", $user_id)){
        getResult(-1, "bind_param wrong", "");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute wrong", "");
    }

    $res = $stmt->get_result();
    while($row = $res->fetch_array()){
        $data[] = $row;
    }
    

    getResult(1, "Show course successfully", $data);
}




?>