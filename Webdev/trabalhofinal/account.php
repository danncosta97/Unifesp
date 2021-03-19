<!DOCTYPE html>
<html>

  <?php
    require('connectionDB.php');

    $idusers = $_GET['idusers'];
    $first_name = $_POST['first_name'];
    $last_name = $_POST['last_name'];
    $dd = $_POST['dd'];
    $mm = $_POST['mm'];
    $yyyy = $_POST['yyyy'];
    $cpf = $_POST['cpf'];
    $email = $_POST['email'];
    $userpw = $_POST['userpw'];
    $phone = $_POST['phone'];
    $cep = $_POST['cep'];
    $city = $_POST['city'];
    $state = $_POST['state'];
    $country = $_POST['country'];
    $address = $_POST['address'];
    $address_number = $_POST['address_number'];
    $address_plus = $_POST['address_plus'];

    $error_state=0;

    if(isset($_POST['updateaccount'])) {  //stay on page on update
      if($idusers == '' || $first_name == '' || $last_name == '' || $dd == ''
         || $mm == '' || $yyyy == '' || $cpf == '' || $email == ''
         || $userpw == '' || $phone == '' || $cep == '' || $city == '' || $state == ''
         || $country == '' || $address == '' || $address_number == ''){
         $error_state =-1;
      }
      else{
        $birth_insert = $yyyy. '-'. $mm. '-'. $dd;
        $sql = "UPDATE users
                SET first_name = '$first_name', last_name = '$last_name', birth = '$birth_insert', cpf = '$cpf', email = '$email', userpw = MD5('$userpw'),
                    cep = '$cep', city = '$city', state = '$state', country = '$country', address = '$address', address_number = '$address_number',
                    address_plus = '$address_plus', phone = '$phone'
                WHERE idusers = '$idusers'";

        if ($db_connection->query($sql) === TRUE) {
          //echo "Record updated successfully";
          $error_state=10;
        } else {
          echo "Error updating record: " . $db_connection->error;
          $error_state=-1;
        }
        unset($_POST['updateaccount']);
        $userpw='';
      }
    }
    else if(isset($_POST['deleteaccount'])) { //back to notes on delete
      // sql to delete a record
      $sql = "DELETE FROM users WHERE idusers = '$idusers'";
      if ($db_connection->query($sql) === TRUE) {
        //echo "Record deleted successfully";
      } else {
        //echo "Error deleting record: " . $db_connection->error;
        $error_state=-1;
      }
      echo 'hiDEL';
      $idusers = '';
      $first_name = '';
      $last_name = '';
      $dd = '';
      $mm = '';
      $yyyy = '';
      $cpf = '';
      $email = '';
      $userpw = '';
      $phone = '';
      $cep = '';
      $city = '';
      $state = '';
      $country = '';
      $address = '';
      $address_number = '';
      $address_plus = '';
      unset($_POST['deleteaccount']);
      header('Location:deletedaccount.php');
      exit();
    }
    else{
      $sql = "SELECT first_name, last_name, birth, cpf, email, userpw,
                                            cep, city, state, country, address, address_number,
                                            address_plus, phone
              FROM users
              WHERE idusers = '$idusers'";
      $result = $db_connection->query($sql);
      if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $first_name = $row['first_name'];
        $last_name = $row['last_name'];
        $birth = $row['birth'];
        $cpf = $row['cpf'];
        $email = $row['email'];
        $userpw = '';
        $cep = $row['cep'];
        $city = $row['city'];
        $state = $row['state'];
        $country = $row['country'];
        $address = $row['address'];
        $address_number = $row['address_number'];
        $address_plus = $row['address_plus'];
        $phone = $row['phone'];
      }
      else {
        header("Location:login.php");
      }
      $birth_split = explode("-", $birth);
      $dd = $birth_split[2];
      $mm = $birth_split[1];
      $yyyy = $birth_split[0];
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
    <title>Perfil de <?php echo $first_name; ?></title>
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
        <li><a href= <?php echo $link_insert; ?> > CRIAR TAREFA </a></li>
        <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
        <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
      </ul>
    </div>

    <h1 style="text-align:center; font-family: Franklin Gothic Medium;">DADOS DA CONTA</h1>
    <div class="form_box">

      <form action=<?php echo $link_account; ?> method="post" autocomplete="off">

        <div class="centertext"> <?php if($error_state==-1) echo '<span style="color:crimson">Erro! Preencha os campos corretamente!</span>';
                                       if($error_state==10) echo '<span style="color:green">Dados atualizados com sucesso!</span>';
                                       else echo ""; ?>
        </div>

        <div style="width:38%; display: inline-block">
          <label for="nome" style="font-family: Franklin Gothic Medium; margin-left:15px;">Nome *</label>
          <input type="text" name="first_name" value="<?php echo $first_name ?>" style="width:100%">
        </div>

        <div style="width:38%; display: inline-block">
          <label for="sobrenome" style="font-family: Franklin Gothic Medium; margin-left:15px;">Sobrenome *</label>
          <input type="text" name="last_name" value="<?php echo $last_name ?>" style="width:100%">
        </div>

        <div style="width:20%; min-width:200px; display: inline-block; margin-left:15px;">
          <label for="birth" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%; display:block;">Data de Nascimento *</label>
          <input type="number" name="dd" value="<?php echo $dd ?>" style="width:20%; margin-left: 0px; margin-right: 0px;  min-width:20%; text-align:center;">
          <input type="number" name="mm" value="<?php echo $mm ?>" style="width:20%; margin-left: 0px; margin-right: 0px; min-width:20%; text-align:center;">
          <input type="number" name="yyyy" value="<?php echo $yyyy ?>" style="width:55%; margin-left: 0px; margin-right: 0px; min-width:40%; text-align:center;">
        </div>

        <div style="width:12%; min-width:200px; display: inline-block">
          <label for="cpf" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">CPF *</label>
          <input type="number" name="cpf" value="<?php echo $cpf ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:40%; min-width:200px; display: inline-block">
          <label for="email" style="font-family: Franklin Gothic Medium; margin-left:15px;">E-mail *<?php if($error_state==1) echo '<span style="color:crimson"> (Esse e-mail já foi cadastrado) </span>'; else echo "";?> </label>
          <input class="<?php if($error_state==1) echo "inputerror"; else echo "";?> " type="email" name="email" value="<?php echo $email ?>" style="width:100%">
        </div>

        <div style="width:30%; display: inline-block">
          <label for="userpw" style="font-family: Franklin Gothic Medium; margin-left:15px;">Senha *</label>
          <input type="password" name="userpw" value="<?php echo $userpw ?>" style="width:100%">
        </div>

        <div style="width:12%; min-width:200px; display: inline-block">
          <label for="phone" style="font-family: Franklin Gothic Medium; margin-left:15px;">Telefone/Celular *</label>
          <input type="number" name="phone" value="<?php echo $phone ?>" style="width:100%">
        </div>


        <div style="width:12%; min-width:200px; display: inline-block">
          <label for="cep" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">CEP *</label>
          <input type="number" name="cep" value="<?php echo $cep ?>" style="width:100%;">
        </div>

        <div style="width:15%; min-width:100px; display: inline-block; margin-left: 15px;">
          <label for="cidade" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">Cidade *</label>
          <input type="text" name="city" value="<?php echo $city ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:15%; min-width:200px; display: inline-block">
          <label for="estado" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">Estado *</label>
          <input type="text" name="state" value="<?php echo $state ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:10%; min-width:120px; display: inline-block">
          <label for="country" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">País *</label>
          <select id="country" name="country" style="width:95%">
            <option <?php if($country=='brazil'){echo("selected");}?> value="brazil" style="width:55%; margin-left: 0px; margin-right: 0px; min-width:40%; text-align:center;">Brasil</option>
            <option <?php if($country=='other'){echo("selected");}?> value="other" style="width:55%; margin-left: 0px; margin-right: 0px; min-width:40%; text-align:center;">Outro</option>
          </select>
        </div>

        <div style="width:30%; min-width:200px; display: inline-block">
          <label for="rua" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">Endereço *</label>
          <input type="text" name="address" value="<?php echo $address ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:5%; min-width:90px; display: inline-block">
          <label for="numero" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">Número *</label>
          <input type="number" name="address_number" value="<?php echo $address_number ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:10%; min-width:120px; display: inline-block">
          <label for="complemento" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">Complemento</label>
          <input type="text" name="address_plus" value="<?php echo $address_plus ?>" style="width:100%; margin-left:0px;">
        </div>

        <br>

        <div class="centertext" style="width:49%; min-width:100px; display:inline">
          <input type="submit" name="deleteaccount" value="Deletar Conta" style="width:49%;margin-top:10px; margin-bottom:10px;">
        </div>

        <div class="centertext" style="width:49%; min-width:100px; display:inline">
          <input type="submit" name="updateaccount" value="Atualizar" style="width:49%;margin-top:10px; margin-bottom:10px;">
        </div>

        <div style="text-align: left"> (*) Preenchimento obrigatório
        </div>

      </form>
    </div>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>
</html>
