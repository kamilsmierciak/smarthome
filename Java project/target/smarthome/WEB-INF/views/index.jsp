<%@ taglib prefix="spring" uri="http://www.springframework.org/tags" %>
<%@ taglib uri = "http://java.sun.com/jsp/jstl/core" prefix = "c" %>
<%--
  Created by IntelliJ IDEA.
  User: kamil
  Date: 08.08.18
  Time: 17:28
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" isELIgnored="false" %>
<html>
<head>

    <c:url value="/resources/css/home.css" var="home"/>
    <link href="${home}" rel="stylesheet"/>
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
    <c:url value="/resources/js/home.js" var="js"/>
    <c:url value="/resources/js/jscolor.js" var="jscolor"/>
    <script src="${js}"></script>
    <script src="${jscolor}"></script>

    <title>Welcome home!</title>
    <link rel="stylesheet" href="../../resources/css/home.css">
</head>
<body>
<div class="jumbotron text-center" id="welcome">Your home status</div>
<div class="container">
    <div class="row h100">
        <div class="col module btn" id="lights">Światła</div>
        <div class="col module btn" id="fan">Zasilanie</div>
        <div class="col module btn" id="drive">Chmura</div>
    </div>
    <div class="row h25"></div>
    <div class=" row justify-content-center h100 ">
        <div class="col module " id="colorpicker">
            Stan świateł/kolor
            <input class="jscolor" value="000000" id="colorPickerInput">
        </div>
        <div class="col module">Stan zasilania<br>
        <p id="stat"></p></div>

    </div>
</div>
</body>
</html>
