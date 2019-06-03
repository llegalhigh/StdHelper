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
    getResult(-1, "数据库连接错误", "");
}
$con->query("SET NAMES utf8mb4");

function judgeNull($content, $information){
    if($content == null){
        getResult(-1, $information."不能为空", "");
    }
}

function judgeMax($content, $information, $number){
    if(iconv_strlen($content,"utf-8") > $number){
        getResult(-1, $information."不能超过".$number."个字符", "");
    }
}

function login($username, $password){
    global $con;
    $sql = "SELECT count(`id`) as `num` FROM `userInformation` WHERE `username`=? AND `password`=?";

    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare错误", "");
    }

    if(!$stmt->bind_param("ss", $username, $password)){
        getResult(-1, "bind_param错误", "");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute错误", "");
    }

    $res = $stmt->get_result();
    $row = $res->fetch_array();
    if($row["num"] == 0){
        getResult(-1, "账号或密码错误", "");
    }

    getResult(0, "登陆成功", "");
}

function judgeSame($password, $checkpwd){
    if($password != $checkpwd){
        getResult(-1, "两次密码不一致", "");
    }
}

function register($username, $password){
    global $con;
    $sql = "SELECT count(`id`) as `num` FROM `userInformation` WHERE `username`=?";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare错误", "1");
    }

    if(!$stmt->bind_param("s", $username)){
        getResult(-1, "bind_param错误", "1");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute错误", "1");
    }

    $res = $stmt->get_result();
    $row = $res->fetch_array();
    if($row["num"] != 0){
        getResult(-1, "用户名已存在", "");
    }

    $sql = "INSERT INTO `userInformation`(`username`,`password`) VALUES (?,?)";
    $stmt = $con->prepare($sql);
    if(!$stmt){
        getResult(-1, "prepare错误", "2");
    }

    if(!$stmt->bind_param("ss", $username, $password)){
        getResult(-1, "bind_param错误", "2");
    }

    if(!$stmt->execute()){
        getResult(-1, "execute错误", "2");
    }

    getResult(0, "注册成功", "");
}







?>