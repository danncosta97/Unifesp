<!DOCTYPE html>
<html>
  <head>

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

      if(isset($_POST['deadline'])){
        $sql = "SELECT idtasks, title, note_description, deadline, difficult FROM tasks WHERE idusers = '$idusers' ORDER BY deadline";
      }elseif (isset($_POST['title'])) {
        $sql = "SELECT idtasks, title, note_description, deadline, difficult FROM tasks WHERE idusers = '$idusers' ORDER BY title";
      }elseif (isset($_POST['difficult'])) {
        $sql = "SELECT idtasks, title, note_description, deadline, difficult FROM tasks WHERE idusers = '$idusers' ORDER BY difficult";
      }else {
        $sql = "SELECT idtasks, title, note_description, deadline, difficult FROM tasks WHERE idusers = '$idusers'";
      }

      $result = $db_connection->query($sql);
      //echo $result->num_rows;

      $db_data = [];
      //echo $row["idtasks"];
      if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
          array_push($db_data, $row["idtasks"], $row["title"], $row["note_description"], $row["deadline"], $row["difficult"]);
        }
      }
      //for($i=0; $i<count($db_data); $i++){
      //  echo $db_data[$i];
      //}

      $sql = "SELECT first_name, last_name, birth, cpf, email, userpw,
                                            cep, city, state, country, address, address_number,
                                            address_plus, phone FROM users WHERE idusers = '$idusers'";
      $result_info = $db_connection->query($sql);

      if ($result_info->num_rows > 0) {
        $row_info = $result_info->fetch_assoc();
        $usersfirst_name = $row_info['first_name'];
        $userslast_name = $row_info['last_name'];
      }

      if(isset($idusers)){
        $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/home.php?idusers='.$idusers;
        $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/noteinsert.php?idusers='.$idusers;
        $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/account.php?idusers='.$idusers;
        $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php?idusers='.$idusers;
        $greetings = 'Olá, '. $usersfirst_name. '! Essas são suas tarefas !';
      }
      else {
        $link_home = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
        $link_insert = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
        $link_account = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
        $link_login = 'http://webdev.zapto.org/danielcosta/trabalhofinal/login.php';
        $greetings = 'Você não parece estar logado !!!';
        //$error_state=14; //Faça Log In
      }

     ?>

    <title>Tarefas de <?php echo $usersfirst_name; ?></title>
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
        padding: 10px 20px;
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
        padding: 20px;
        width: 360px;
      }

      .form_box_sort {
        border-radius: 10px;
        background-color: Gainsboro;
        margin-top: 1%;
        margin-bottom: 1%;
        margin-left: auto;
        margin-right: auto;
        padding: 10px;
        width: 80%;
      }

      .notes_container{
        width: 80%;
        background-color:white;
        margin-left: auto;
        margin-right: auto;
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


      button {
          border-bottom-left-radius: 5px;
          border-bottom-right-radius: 5px;
          width: 200px;
          height: 200px;
          padding: 10px;
          margin: 10px;
      }

      #button-holder {
        display: inline-flex;
        width: 100%;
        height: auto;
        flex-wrap: wrap;
        white-space: pre;
        justify-content: space-evenly;
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

    <h1 style="text-align:center; font-family: Franklin Gothic Medium;"><?php echo $greetings ?></h1>

    <div class="form_box_sort">
      <form action=<?php echo $link_home; ?> method="post" autocomplete="off">

        <div class="centertext">

          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="submit" name="default" value="Padrão" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="submit" name="deadline" value="Prazo" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="submit" name="title" value="Título" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

          <div style="width:10%; min-width:100px; display:inline-flex; justify-content: center">
            <input type="submit" name="difficult" value="Dificuldade" style="width:100%;margin-top:10px; margin-bottom:10px;">
          </div>

        </div>
      </form>
    </div>

    <div class="notes_container">
      <script>
        window.onload = function(){
          generate();
        }
      </script>
      <div id="button-holder"></div>
    </div>

    <div class="">
      <p style="text-align: center; background-color:Gainsboro">Autor: Daniel Barbosa Silva Costa (112185)<br>Email: <a href="mailto:daniel.barbosa21@unifesp.br"> daniel.barbosa21@unifesp.br </a><br></p>
    </div>

  </body>

  <script type="text/javascript">
    function generate(){
      let buttonsToGenerate = <?php echo $result->num_rows ?>;
      var k=0;
      var jArray = <?php echo json_encode($db_data); ?>;
      var descr = "";
      for(let i = 0; i < buttonsToGenerate; i++){
        desc_size = jArray[2+5*i].length;
        if(desc_size > 0){
          descr = desc_org(jArray[2+5*i].substring(0,55), desc_size);
        }

        var taskid_ = jArray[0+5*i];
        var title_ = jArray[1+5*i];
        //var desc_ -> descr
        var date_ = jArray[3+5*i];
        var difficult_ = jArray[4+5*i];
        var daystogo = get_days(date_);


        var _taskid = document.createElement('span');
        _taskid.style.color = 'grey';
        var t = document.createTextNode('# '+ taskid_);
        _taskid.appendChild(t);


        var _title = document.createElement('span');
        _title.style.fontWeight = 'bold';
        _title.style.color = 'blue';
        t = document.createTextNode('\n\n'+ title_);
        _title.appendChild(t);


        var _desc = document.createElement('span');
        _desc.style.color = 'black';
        t = document.createTextNode('\n\n'+ descr + '\n\n');
        _desc.appendChild(t);


        var _date = document.createElement('span');
        var _dateplus = "\n (~ "+daystogo+' dias restantes) ';
        _date.style.color = 'black';
        if(daystogo<7 && daystogo>0){
          _date.style.backgroundColor = "lightcoral";
        }
        else if(daystogo>=7 && daystogo<30){
          _date.style.backgroundColor = "#FFFF65"; //yellow
        }
        else if (daystogo>=30){
          _date.style.backgroundColor = "lightgreen";
        }
        else {
          _date.style.backgroundColor = "darkgrey";
          _dateplus="";
        }
        if (daystogo<0) {
          t = document.createTextNode(' Encerrado em ' + date_ + ' '+_dateplus);
        }
        else {
          t = document.createTextNode(' Realizar até ' + date_ + ' '+_dateplus);
        }
        _date.appendChild(t);


        var _difficult = document.createElement('span');
        _difficult.style.width = '100%';
        _difficult.style.backgroundColor = 'darkkhaki';
        _difficult.style.fontWeight = 'bold';
        if(difficult_ >=9){
          _difficult.style.color = 'red';
          t = document.createTextNode('\n\n MUITO DIFÍCIL ');
        }else if(difficult_ >=7 && difficult_ <=8){
          _difficult.style.color = 'orange';
          t = document.createTextNode('\n\n DIFÍCIL ');
        }else if(difficult_ >=5 && difficult_ <=6){
          _difficult.style.color = 'yellow';
          t = document.createTextNode('\n\n REGULAR ');
        }else if(difficult_ >=3 && difficult_ <=4){
          _difficult.style.color = 'greenyellow';
          t = document.createTextNode('\n\n FÁCIL ');
        }else if(difficult_ >=1 && difficult_ <=2){
          _difficult.style.color = 'lime';
          t = document.createTextNode('\n\n MUITO FÁCIL ');
        }
        _difficult.appendChild(t);

        var btn = document.createElement("button");
        btn.style.backgroundColor = "khaki";
        //var t = document.createTextNode('#'+ _idtask +'\n\n'+ jArray[1+5*i] +'\n\n'+ descr +'\n\n'+ jArray[3+5*i] +'\n\n'+ jArray[4+5*i]);
        btn.appendChild(_taskid);
        btn.appendChild(_title);
        btn.appendChild(_desc);
        btn.appendChild(_date);
        btn.appendChild(_difficult);
        //button shadow based timeleft to do task

        if(daystogo<7 && daystogo>0){
          btn.style.boxShadow = "0px 0px 20px 10px lightcoral";
        }
        else if(daystogo>=7 && daystogo<30){
          btn.style.boxShadow = "0px 0px 20px 10px #FFFF65"; //yellow
        }
        else if (daystogo>=30){
          btn.style.boxShadow = "0px 0px 20px 10px lightgreen";
        }
        else {
          btn.style.backgroundColor = "darkgrey";
        }
        btn.addEventListener("click", redirect);

        var b = document.getElementById('button-holder').appendChild(btn);
        //b.addEventListener("click", redirect);
      }
    }

    function redirect(){
      var id_redirect = event.currentTarget.innerText;
      var id_task_get = id_redirect.substring(2, id_redirect.indexOf('\n'));
      var link_note = 'note.php?idusers='+<?php echo $idusers; ?>+'&idtasks='+id_task_get;
      //window.alert(id_task_get);
      window.location = link_note;
    }

    function desc_org(str, str_size){
      //window.alert("hihi");
      var sp = str.split(" ");
      var sres="";
      var size=0;
      for(let i=0; i<sp.length; i++){
        //window.alert(sp[i]);
        size += sp[i].length;
        if(size<20){
          sres += sp[i] + " ";
        }
        else{
          size = sp[i].length;
          sres += '\n' + sp[i] + " ";
        }
        //window.alert(sres);
      }
      //window.alert(sres);
      if(str_size>55){
        sres += '...'
      }
      return sres;
    }

    function get_days(strdate){

      var sp = strdate.split("-"); //yyyy mm dd
      var days=0;//window.alert("1");
      var today = new Date();
      //window.alert(parseInt(sp[1])+'-'+today.getMonth());
      var y = parseInt(sp[0]) - today.getFullYear();//window.alert("2");
      var m = parseInt(sp[1]) - (today.getMonth() + 1);//window.alert("3");
      var d = parseInt(sp[2]) - today.getDate();//window.alert("4");

      days = y*365 + m*30 + d;
      if(y<0){
        days = -1;
      } else if (m<0 && y==0){
        days = -1;
      } else if (d<0 && m==0 && y==0){
        days = -1;
      }
      //window.alert(days);
      return (days);
    }

  </script>

</html>
