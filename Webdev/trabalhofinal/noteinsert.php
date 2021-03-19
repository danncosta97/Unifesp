<!DOCTYPE html>
<html>

  <?php
    require('connectionDB.php');

    $idusers = $_GET['idusers'];
    $sql = "SELECT first_name, last_name, birth, cpf, email, userpw,
                                          cep, city, state, country, address, address_number,
                                          address_plus, phone FROM users WHERE idusers = '$idusers'";
    $result_info = $db_connection->query($sql);

    if ($result_info->num_rows > 0) {
      $row_info = $result_info->fetch_assoc();
      $usersfirst_name = $row_info['first_name'];
      $userslast_name = $row_info['last_name'];
    }
    else{
      header("Location:login.php");
    }

    $title = $_POST['title'];
    $dd = $_POST['dd'];
    $mm = $_POST['mm'];
    $yyyy = $_POST['yyyy'];
    $note_description = $_POST['note_description'];
    $difficult = $_POST['difficult'];
    echo $_POST['update'];
    $error_state=0;
    if(isset($_POST['insert'])) {  //stay on page
      if($title == '' || $dd == '' || $mm == '' || $yyyy == '' || $difficult == ''){
         $error_state =-1;
      }
      else{
        $deadline_insert = $yyyy. '-'. $mm. '-'. $dd;
        if($difficult>10){
          $difficult=10;
        } else if($difficult<1){
          $difficult=1;
        }
        $stmt = $db_connection->prepare("INSERT INTO tasks (title, note_description, deadline, difficult, idusers)
                                         VALUES (?, ?, ?, ?, ?)");
        $stmt->bind_param('sssii', $title, $note_description, $deadline_insert, $difficult, $idusers);
        $stmt->execute();

        if($errorn = mysqli_errno($db_connection)){
          //echo mysqli_error($db_connection);
          $error_state = -1;
        }
        else {
          echo "Inserido com sucesso";
          header("Location: home.php?idusers=$idusers");
          exit();
        }
      }
    }

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
    <title>Criação de Tarefa</title>
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
        background-color: khaki;
        margin-top: 20px;
        margin-left:auto;
        margin-right:auto;
        padding: 20px;
        min-width: 640px;
        width: 640px;
      }

    </style>
  </head>

  <body>

    <div style="min-width:720px;"> <!-- barra de navegação -->
      <ul class="nav">
        <li><a href= <?php echo $link_home; ?> > HOME </a></li>
        <li><a href= <?php echo $link_insert; ?> > CRIAR TAREFA </a></li>
        <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
        <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
      </ul>
    </div>

    <div class="form_box">

      <form action=<?php echo $link_insert; ?> method="post" autocomplete="off">

        <div class="centertext"> <?php if($error_state==-1) echo '<span style="color:crimson">Erro! Preencha os campos corretamente</span>';
                                       else echo ""; ?>
        </div>

        <div style="width:60%; margin:auto">
          <label for="title" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%; display:block;">Título *</label>
          <input type="text" name="title" value="<?php echo $title; ?>" style="width:100%">
        </div>

        <div style="width:60%; margin:auto">
          <label for="birth" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%; display:block;">Realizar até (dia - mês - ano) *</label>
          <input type="number" name="dd" value="<?php echo $dd ?>" style="width:28%; margin-left: 0px; margin-right: 0px; text-align:center;">
          <input type="number" name="mm" value="<?php echo $mm ?>" style="width:27%; margin-left: 0px; margin-right: 0px; text-align:center;">
          <input type="number" name="yyyy" value="<?php echo $yyyy ?>" style="width:38%; margin-left: 0px; margin-right: 0px; text-align:center;">
        </div>

        <div style="width:60%; margin:auto">
          <label for="difficult" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%; display:block;">Dificuldade (número de 1 à 10) *</label>
          <input type="number" name="difficult" value="<?php echo $difficult; ?>" style="width:100%; margin-left:0px;">
        </div>



        <br>

        <div style="width:60%; margin:auto">
          <label for="note_description" style="font-family: Franklin Gothic Medium; margin-left:15px; display:block;">Descrição</label>
          <textarea name="note_description" rows="8" cols=100% style="width:100%; margin-left:0px;resize:vertical"><?php echo $note_description; ?></textarea>
        </div>


        <br>
        <div class="centertext">
          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="reset" value="Redefinir" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="submit" name="insert" value="Criar" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

          <div style="text-align: left"> (*) Preenchimento obrigatório
          </div>
        </div>

      </form>
    </div>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>
</html>
