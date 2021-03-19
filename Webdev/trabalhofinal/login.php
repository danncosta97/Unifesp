<!DOCTYPE html>
<html>
  <head>
    <title>Login</title>
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

      .form_box {
        border-radius: 10px;
        background-color: Gainsboro;
        margin-top: 12%;
        margin-bottom: 15%;
        margin-left: auto;
        margin-right: auto;
        padding-left: 20px;
        padding-right: 20px;
        padding-top: 20px;
        padding-bottom:10px;
        width: 360px;
      }

      input[type=text], input[type=email], input[type=number], input[type=password], select, textarea{
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


      input[type=text]:focus, input[type=email]:focus, input[type=number]:focus, input[type=password]:focus, textarea:focus{
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

    </style>
  </head>

  <body>

    <?php
      require('connectionDB.php');

      $email = $_POST['email'];
      $userpw = $_POST['userpw'];
      $idusers = $_GET['idusers'];

      $error_state=0;

      if($_POST['signup']=='Sign Up'){
        header('Location:register.php');
      }
      else if($_POST['login']=='Log In'){
        //check for null itens
        if($email == "") $null_email=1;
        else $null_email=0;

        if($userpw == "") $null_userpw=1;
        else $null_userpw=0;

        //check for null itens before insert in db
        //all null
        if($null_email==1 && $null_userpw==1){
            $error_state=2; //null variables
        }
        //some null
        else if($null_email==1 || $null_userpw==1){
            $error_state=3; //null variables
        }
        //no null variables
        else{

          $sql = "SELECT idusers FROM users WHERE email = '$email' and userpw = MD5('$userpw')";
          $result = $db_connection->query($sql);

          if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            $idusers = $row["idusers"];
            header('Location:home.php?idusers='.$idusers);
            $error_state=7;
          }
          else{
            $error_state=8;
          }

          if($errorn = mysqli_errno($db_connection)){
            if($errorn=='1062') {
              echo "emaillllll";
              $error_state=1; //email ja cadastrado
            }
            else if($errorn=='1048' || $errorn=='1292'){
              echo "nulllll";
              $error_state=2; //null variables by mysql || date type incorrect (probably due non filled fields)
            }
            else if($errorn=='1406'){
              echo "looooongo";
              $error_state=4; //size too long
            }
            else if($errorn=='1364'){
              echo "db nooooovo";
              $error_state=5; //db has more variables
            }
            else {
              echo $errorn;
              echo mysqli_error($db_connection);
              $error_state=-1; //unknow
            }
          }
        }
        $userpw='';
      }

      if(isset($idusers)){
        $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/home.php?idusers='.$idusers;
        $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/noteinsert.php?idusers='.$idusers;
        $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/account.php?idusers='.$idusers;
        $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php?idusers='.$idusers;
      }
      else {
        $link_home = '';
        $link_insert = '';
        $link_account = '';
        $link_login = '';
        //$error_state=14; //Faça Log In
      }


     ?>

     <div style="min-width:720px;"> <!-- barra de navegação -->
       <ul class="nav">
         <li><a href= <?php echo $link_home; ?> > HOME </a></li>
         <li><a href= <?php echo $link_insert; ?> > CRIAR TAREFA </a></li>
         <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
         <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
       </ul>
     </div>

    <h1 style="text-align:center; font-family: Franklin Gothic Medium;">Crie e gerencie suas tarefas</h1>

    <div class="form_box">

      <form action="login.php" method="post" autocomplete="off">

        <div class="centertext" style="margin-bottom:10px;"> <?php if($error_state==4) echo '<span style="color:crimson">Algum(ns) campo(s) possui(em) uma quantidade de caracteres acima do permitido</span>';
                                       else if($error_state==2 || $error_state==3) echo '<span style="color:crimson">Insira o e-mail e a senha</span>';
                                       else if($error_state==5) echo '<span style="color:crimson">Server side error</span>';
                                       else if($error_state==-1) echo '<span style="color:crimson">Erro desconhecido</span>';
                                       else if($error_state==8) echo '<span style="color:crimson">Usuário e/ou senha incorreto(s)</span>';
                                       else if($error_state==14) echo '<span style="color:crimson">Faça Log In ou cadastre-se!</span>';
                                       else echo ""; ?>
        </div>

        <div class="centertext" style="width:98%; min-width:120px; display: inline-block">
          <label for="email" style="font-family: Franklin Gothic Medium; width:100%">E-mail</label>
          <input type="email" name="email" value="<?php echo $email ?>" style="width:100%;">
        </div>

        <br>

        <div class="centertext" style="width:98%; min-width:120px; display: inline-block">
          <label for="userpw" style="font-family: Franklin Gothic Medium; width:100%">Senha</label>
          <input type="password" name="userpw" value="<?php echo $userpw ?>" style="width:100%;">
        </div>

        <br>

        <div style="width:48%; min-width:100px; display:inline-block">
          <input type="submit" value="Log In" name="login" style="width: 100%; margin-top:10px; margin-bottom:10px;">
        </div>

        <div style="width:49%; min-width:100px; display:inline-block">
          <input type="submit" value="Sign Up" name="signup" style="width: 100%; margin-top:10px; margin-bottom:10px;">
        </div>

        <br>

        <div class="centertext" style="margin-bottom:10px;"> <a style="text-decoration:none" href="redefinepwemail.php">Esqueci minha senha</a></div>


      </form>
    </div>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>
</html>
