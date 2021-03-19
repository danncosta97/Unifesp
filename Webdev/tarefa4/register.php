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

    //check for null itens
    if(is_null( $first_name )) $null_first_name=1;
    else{
      $null_first_name=0;
    }
    if(is_null( $last_name )) $null_last_name=1;
    else{
      $null_first_name=0;
    }
    if(is_null( $dd )) $null_dd=1;
    else{
      $null_dd=0;
    }
    if(is_null( $mm )) $null_mm=1;
    else{
      $null_mm=0;
    }
    if(is_null( $yyyy )) $null_yy=1;
    else{
      $null_yy=0;
    }
    if(is_null( $cpf )) $null_cpf=1;
    else{
      $null_cpf=0;
    }
    if(is_null( $email )) $null_email=1;
    else{
      $null_email=0;
    }
    if(is_null( $userpw )) $null_userpw=1;
    else{
      $null_userpw=0;
    }
    if(is_null( $phone )) $null_phone=1;
    else{
      $null_phone=0;
    }
    if(is_null( $cep )) $null_cep=1;
    else{
      $null_cep=0;
    }
    if(is_null( $city )) $null_city=1;
    else{
       $null_city=0;
     }
    if(is_null( $state )) $null_state=1;
    else{
      $null_state=0;
    }
    if(is_null( $country )) $null_country=1;
    else{
       $null_country=0;
     }
    if(is_null( $address )) $null_addres=1;
    else{
      $null_addres=0;
    }
    if(is_null( $address_number )) $null_address_number=1;
    else{
      $null_address_number=0;
    }
    if(is_null( $address_plus )) $null_address_plus=1;
    else{
      $null_address_plus=0;
    }

    //check for null itens before insert in db
    //all null
    if($null_first_name==1 && $null_last_name==1 &&  $null_dd==1 && $null_mm==1 &&
      $null_yy==1 && $null_cpf==1 && $null_email==1 && $null_userpw==1 && $null_phone==1 && $null_cep==1 &&
      $null_city==1 &&  $null_state==1 && $null_country==1 && $null_addres==1 &&
      $null_address_number==1 && $null_address_plus==1){
        $error_state=0; //null variables
    }
    //some null
    else if($null_first_name==1 || $null_last_name==1 ||  $null_dd==1 || $null_mm==1 ||
            $null_yy==1 || $null_cpf==1 || $null_email==1 || $null_userpw==1 || $null_phone==1 || $null_cep==1 ||
            $null_city==1 ||  $null_state==1 || $null_country==1 || $null_addres==1 ||
            $null_address_number==1 || $null_address_plus==1){
        $error_state=3; //null variables
    }
    //no null variables
    else{
      $userpw = md5($userpw);
      $date = $yyyy. '-'. $mm. '-'. $dd;
      $stmt = $db_connection->prepare("INSERT INTO users (first_name, last_name, birth, cpf, email, userpw,
                                            cep, city, state, country, address, address_number,
                                            address_plus, phone)
                                       VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
      $stmt->bind_param('sssssssssssiss', $first_name, $last_name, $date, $cpf, $email, $userpw, $cep, $city,  $state, $country, $address,
                        $address_number, $address_plus, $phone);
      $stmt->execute();
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
      else{
        $sql = "SELECT idusers FROM users WHERE email = '$email'";
        $result_info = $db_connection->query($sql);

        if ($result_info->num_rows > 0) {
          $row_info = $result_info->fetch_assoc();
          $idusers = $row_info['idusers'];
        }
        header("Location:registersuccess.php?idusers=$idusers");
        exit();
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
        <li><a href= <?php echo $link_insert; ?> > CRIAR NOTA </a></li>
        <li><a href= <?php echo $link_account; ?> > CONTA </a></li>
        <li style="float:right"><a href= <?php echo $link_login; ?> > LOG IN </a></li>
      </ul>
    </div>

    <h2 style="text-align:center">CADASTRO</h2>
    <div class="form_box">

      <form action="register.php" method="post" autocomplete="off">

        <div class="centertext"> <?php if($error_state==4) echo '<span style="color:crimson">Algum(ns) campo(s) possui(em) uma quantidade de caracteres acima do permitido</span>';
                                       else if($error_state==2 || $error_state==3) echo '<span style="color:crimson">Preencha os campos obrigatórios</span>';
                                       else if($error_state==5) echo '<span style="color:crimson">Server side error</span>';
                                       else if($error_state==-1) echo '<span style="color:crimson">Erro desconhecido</span>';
                                       else echo ""; ?>
        </div>

        <div style="width:49%; display: inline-block">
          <label for="nome" style="font-family: Franklin Gothic Medium; margin-left:15px;">Nome *</label>
          <input type="text" name="first_name" value="<?php echo $first_name ?>" style="width:100%">
        </div>

        <div style="width:50%; display: inline-block">
          <label for="sobrenome" style="font-family: Franklin Gothic Medium; margin-left:15px;">Sobrenome *</label>
          <input type="text" name="last_name" value="<?php echo $last_name ?>" style="width:100%">
        </div>

        <div style="width:15%; min-width:200px; display: inline-block">
          <label for="birth" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%; display:block;">Data de Nascimento (dia - mês - ano)*</label>
          <input type="number" name="dd" value="<?php echo $dd ?>" style="width:20%; margin-left: 0px; margin-right: 0px;  min-width:20%; text-align:center;">
          <input type="number" name="mm" value="<?php echo $mm ?>" style="width:20%; margin-left: 0px; margin-right: 0px; min-width:20%; text-align:center;">
          <input type="number" name="yyyy" value="<?php echo $yyyy ?>" style="width:55%; margin-left: 0px; margin-right: 0px; min-width:40%; text-align:center;">
        </div>

        <div style="width:20%; min-width:200px; display: inline-block">
          <label for="cpf" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">CPF *</label>
          <input type="number" name="cpf" value="<?php echo $cpf ?>" style="width:100%; margin-left:0px;">
        </div>

        <div style="width:64%; min-width:200px; display: inline-block">
          <label for="email" style="font-family: Franklin Gothic Medium; margin-left:15px;">E-mail *<?php if($error_state==1) echo '<span style="color:crimson"> (Esse e-mail já foi cadastrado) </span>'; else echo "";?> </label>
          <input class="<?php if($error_state==1) echo "inputerror"; else echo "";?> " type="email" name="email" value="<?php echo $email ?>" style="width:100%">
        </div>

        <div style="width:30%; display: inline-block">
          <label for="userpw" style="font-family: Franklin Gothic Medium; margin-left:15px;">Senha *</label>
          <input type="password" name="userpw" value="<?php echo $userpw ?>" style="width:100%">
        </div>

        <div style="width:64%; min-width:200px; display: inline-block">
          <label for="phone" style="font-family: Franklin Gothic Medium; margin-left:15px;">Telefone/Celular *</label>
          <input type="number" name="phone" value="<?php echo $phone ?>" style="width:100%">
        </div>


        <div style="width:15%; min-width:200px; display: inline-block">
          <label for="cep" style="font-family: Franklin Gothic Medium; margin-left:15px; width:100%">CEP *</label>
          <input type="number" name="cep" value="<?php echo $cep ?>" style="width:100%;">
        </div>

        <div style="width:15%; min-width:100px; display: inline-block">
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
          <input type="number" name="address_plus" value="<?php echo $address_plus ?>" style="width:100%; margin-left:0px;">
        </div>

        <br>

        <div class="centertext" style="width:49%; min-width:100px; display:inline">
          <input type="reset" name="reset" style="width:49%;margin-top:10px; margin-bottom:10px;">
        </div>

        <div class="centertext" style="width:49%; min-width:100px; display:inline">
          <input type="submit" name="send" style="width:49%;margin-top:10px; margin-bottom:10px;">
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
