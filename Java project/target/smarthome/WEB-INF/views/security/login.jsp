<?xml version="1.0" encoding="UTF-8" ?>
<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8" isELIgnored="false" %>
<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib uri = "http://java.sun.com/jsp/jstl/core" prefix = "c" %>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css"
          integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script
            src="https://code.jquery.com/jquery-3.3.1.js"
            integrity="sha256-2Kok7MbOyxpgUVvAk/HJ2jigOSYS2auK4Pfzbm7uH60="
            crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"
            integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"
            integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
            crossorigin="anonymous"></script>
    <%@ include file="jspf/head_config.jspf" %>
    <c:url value="/resources/files/Backyard_4K_Living_Background.mp4" var="wideo"/>
    <c:url value="/resources/css/login.css" var="css"/>
    <link href="${css}" rel="stylesheet"/>

</head>
<body>
<div id="main-movie">
<div id="else">


<%@ include file="jspf/header.jspf" %>
<%@ include file="jspf/main_menu.jspf" %>
<p class='error'>${msg}</p>
<form method="post">
    <div class="container">
        <div class="row justify-content-md-center">
            <div class="col-md-auto">
                <p>
                    Username <input type="text" name="username" placeholder=""/>
                </p>
            </div>
        </div>
            <div class="row justify-content-md-center">
                <div class="col-md-auto">
                    <p>
                        Password <input type="password" name="password" placeholder=""/>
                    </p>
                </div>
            </div>
            <div class="row justify-content-md-center">
                <p>
                    <input type="hidden" name="${_csrf.parameterName}"
                           value="${_csrf.token}"/>
                    <input type="submit"/>
                </p>
            </div>
        </div>


</form>
<%@ include file="jspf/footer.jspf" %>
</div>
    <video autoplay muted loop id="video">
        <source src="${wideo}" type="wideo/mp4">
    </video>
</div>
</body>
</html>