<!DOCTYPE html>
<html>

  <?php
    require('connectionDB.php');
    $idusers = $_GET['idusers'];

    if(isset($idusers)){
      $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/home.php?idusers='.$idusers;
      $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/noteinsert.php?idusers='.$idusers;
      $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/account.php?idusers='.$idusers;
      $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php?idusers='.$idusers;
    }
    else {
      $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      //$error_state=14; //Faça Log In
    }

   ?>

  <head>
    <title>Cadastro - Organizer</title>
    <meta charset="utf-8">
    <style>

      .nav{
        list-style-type: none;
        margin: 0;
        padding: 0;
        overflow: hidden;
        background-color: LightGrey;
      }

      li {
        float: left;
      }

      li a, .dropbtn{
        display: inline-block;
        color: Black;
        text-align: center;
        padding: 10px 15px;
        text-decoration: none;
        font-weight: bold;
        border: 10;
      }

      li a:hover, .dropdown:hover .dropbtn{
        background-color:deepskyblue
      }

      li.dropdown {
        display: inline-block;
      }

      .dropdown-content {
        display: none;
        position: absolute;
        background-color: deepskyblue;
        min-width: 150px;
        box-shadow: 0px 5px 15px 0px rgba(0,0,0,0.4);
        z-index: 1;
      }

      .dropdown-content a {
        color: black;
        padding: 10px 15px;
        text-decoration: none;
        display: block;
        text-align: left;
      }

      .dropdown:hover .dropdown-content {
        display: block;
        background-color: LightGrey;
      }

      .centertext {
        text-align: center;
      }

      .inputerror{
        outline: 0px;
        box-shadow: 0 0 1pt 1pt crimson;
      }

      input[type=text], input[type=email], input[type=number], select, textarea{
        padding: 12px;
        border: 1px solid;
        border-color: rgb(200,200,200);
        border-radius: 20px;
        box-sizing: border-box;
        margin-top: 5px;
        margin-bottom: 10px;
        margin-left: 5px;
        margin-right: 5px;
        resize: none;
      }

      input[type=submit], input[type=reset]{
        padding: 12px;
        border: 2px solid;
        border-color: rgb(100,100,100);
        background-color: rgba(0, 0, 0, 0.2);
        border-radius: 20px;
        box-sizing: border-box;
        margin-top: 5px;
        margin-bottom: 10px;
        margin-left: 5px;
        margin-right: 5px;
        resize: none;
      }


      input[type=text]:focus, input[type=email]:focus, input[type=number]:focus, textarea:focus{
        outline: 0px;
        box-shadow: 0 0 1pt 1pt deepskyblue;
      }



      input[type=submit]:hover, input[type=reset]:hover{
        outline: 0px;
        background-color: rgba(0, 0, 0, 0.1);
        box-shadow: 0 0 1pt 1pt deepskyblue;
      }

      input[type=submit]:hover:active{
        outline: 0px;
        background-color: rgb(100,255,100);
        box-shadow: 0 0 1pt 1pt deepskyblue;
      }

      input[type=reset]:hover:active{
        outline: 0px;
        background-color: rgb(255,100,100);
        box-shadow: 0 0 1pt 1pt deepskyblue;
      }

      /*Remove inner arrows in type numbers*/
      /* Chrome, Safari, Edge, Opera */
      input::-webkit-outer-spin-button,
      input::-webkit-inner-spin-button {
        -webkit-appearance: none;
        margin: 0;
      }
      /* Firefox */
      input[type=number] {
        -moz-appearance: textfield;
      }

      .form_box {
        border-radius: 10px;
        background-color: Gainsboro;
        margin:20px;
        padding: 20px;
        min-width: 640px;
      }

    </style>
  </head>

  <body>

    <div style="min-width:720px;"> <!-- barra de navegação -->
      <ul class="nav">
        <li><a href= <?php echo $link_home; ?> > HOME </a></li>
        <li><a href= <?php echo $link_insert; ?> > CRIAR NOTA </a></li>
        <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
        <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
      </ul>
    </div>

    <h1 style="text-align:center; font-family: Franklin Gothic Medium;">Conta deletada com sucesso! Redirecionando para Log In ...</h1>
    <script type="text/javascript">
      window.onload = function(){
        var link_to_login = "window.location='login.php'";
        setTimeout(link_to_login,3000);
      }
    </script>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>

</html>
