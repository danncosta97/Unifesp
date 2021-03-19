<?php
session_start();
?>

<!DOCTYPE html>
<html>
  <head>
    <title>Redefinição de Senha - Insira o e-mail</title>
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
        margin-top: 1%;
        margin-bottom: 1%;
        margin-left: auto;
        margin-right: auto;
        padding: 20px;
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

      $error_state=0;

      if($_POST['send']=='Enviar'){
        if($email == ''){
          $error_state=2;
        }
        else{
          $sql = "SELECT idusers FROM users WHERE email = '$email'";
          $result = $db_connection->query($sql);
          if ($result->num_rows > 0) {
            $row = $result->fetch_assoc();
            $idusers = $row["idusers"];
            $_SESSION['idusers']=$idusers;
            header('Location:redefinepw.php');
            $error_state=7;
            exit();
          }
          else {
            $error_state=1;
            $_POST['email']=$email;
          }
        }
        unset($_POST['send']);
      }

      $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
      $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';

     ?>

     <div style="min-width:720px;"> <!-- barra de navegação -->
       <ul class="nav">
         <li><a href= <?php echo $link_home; ?> > HOME </a></li>
         <li><a href= <?php echo $link_insert; ?> > CRIAR TAREFA </a></li>
         <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
         <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
       </ul>
     </div>

    <h3 style="text-align:center; font-family: Franklin Gothic Medium;">Redefinição de senha</h3>

    <div class="form_box">

      <form action="redefinepwemail.php" method="post" autocomplete="off">

        <div class="centertext" style="margin-bottom:10px;"> <?php if($error_state==1) echo '<span style="color:crimson">E-mail não encontrado!</span>';
                                                             else if($error_state==2) echo '<span style="color:crimson">Preencha o e-mail!</span>';
                                                             else echo ""; ?>
        </div>

        <div class="centertext" style="width:98%; min-width:120px; display: inline">
          <label for="email" style="font-family: Franklin Gothic Medium; width:100%; margin-left:20px">E-mail cadastrado</label>
          <input type="email" name="email" value="<?php echo $email ?>" style="width:100%;">
        </div>

        <br>

        <div class="centertext">
          <div style="width:48%; min-width:100px; display:inline-block">
            <input type="submit" value="Enviar" name="send" style="width: 100%; margin-top:10px; margin-bottom:10px;">
          </div>
        </div>

      </form>
    </div>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>
</html>
