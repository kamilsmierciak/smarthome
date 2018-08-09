<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%--
  Created by IntelliJ IDEA.
  User: kamil
  Date: 08.08.18
  Time: 17:28
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>

    <spring:url value="/resources/home.css" var="home"/>
    <link href="${home}" rel="stylesheet"/>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css"
          integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"
            integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo"
            crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js"
            integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49"
            crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"
            integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy"
            crossorigin="anonymous"></script>


    <title>Welcome home!</title>
    <link rel="stylesheet" href="../../resources/css/home.css">
</head>
<body>
<div class="jumbotron text-center" id="welcome">Your home status</div>
<div class="container">
    <div class="row h100">
        <div class="col module">Światła</div>
        <div class="col module">Wiatrak</div>
        <div class="col module">Dysk</div>
    </div>
    <div class="row h25"></div>
    <div class=" row justify-content-center h100 ">
        <div class="col module">Stan świateł/kolor</div>
        <div class="col module">Stan wiatraka</div>
        <div class="col module">temperatura pokoju</div>
        <div class="col module">Temperatura pieca</div>
    </div>
</div>
</body>
</html>
