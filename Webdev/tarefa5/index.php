<!DOCTYPE html>
<html>
  <head>
    <title>Tarefa 5 - PHP Básico</title>
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
        min-width: 720px;
      }

    </style>
  </head>

  <body>
    <div> <!-- barra de navegação -->
      <ul class="nav">
        <li><a href="http://webdev.zapto.org/danielcosta/tarefa5/"> HOME </a></li>
      </ul>
    </div>

    <h2 style="text-align:center">Preencha um dos exercícios abaixo e envie no respectivo botão para obter o resultado</h2>

    <div class="form_box">
      <!-- Ex1 -->
      <form action="" method="post">
        <h2>Exercício 1 - Consumo médio de combustível</h2>
        <?php
          static $dist = 485;
          static $comb = 29.8;
        ?>
        <div style="width:32%; display: inline-block">
          <label for="distancia" style="font-family: Franklin Gothic Medium; margin-left:15px;">Distância Percorrida (km)</label>
          <input type="text" name="distancia" id="distancia" placeholder=""
                  value="<?php
                           echo $dist;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:32%; display: inline-block">
          <label for="combustivel" style="font-family: Franklin Gothic Medium; margin-left:15px;">Quantidade de combustível adicionado (Litros)</label>
          <input type="text" name="combustivel" id="combustivel" placeholder=""
                  value="<?php
                            echo $comb;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($dist>0 && $comb>0){
        ?>
          <div style="width:34%; display: inline-block">
            <label for="consumo" style="font-family: Franklin Gothic Medium; margin-left:15px;">Consumo (km/L)</label>
            <input type="text" name="consumo" id="consumo" readonly="readonly"
                    value="<?php
                              echo round($dist/$comb,2);
                              echo ' km/L';
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:34%; display: inline-block">
            <label for="consumo" style="font-family: Franklin Gothic Medium; margin-left:15px;">Consumo (km/L)</label>
            <input type="text" name="consumo" id="consumo" readonly="readonly"
                    value="<?php
                              echo '0 km/L';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>

      </form>
    </div>

    <div class="form_box">
      <!-- Ex2 -->
      <form action="" method="post">
        <h2>Exercício 2 - COVID-19</h2>
        <?php
          $largura = $_POST[largura];
          $comprimento = $_POST[comprimento];
        ?>
        <div style="width:32%; display: inline-block">
          <label for="largura" style="font-family: Franklin Gothic Medium; margin-left:15px;">Largura (m)</label>
          <input type="text" name="largura" id="largura" placeholder=""
                  value="<?php
                           echo $largura;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:32%; display: inline-block">
          <label for="comprimento" style="font-family: Franklin Gothic Medium; margin-left:15px;">Comprimento (m)</label>
          <input type="text" name="comprimento" id="comprimento" placeholder=""
                  value="<?php
                           echo $comprimento;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($largura>0 && $comprimento>0){
        ?>
          <div style="width:34%; display: inline-block">
            <label for="alunos" style="font-family: Franklin Gothic Medium; margin-left:15px;">Quantidade máxima de alunos</label>
            <input type="text" name="alunos" id="alunos" readonly="readonly"
                    value="<?php
                              $size = $comprimento*$largura;
                              echo floor($size/2.25);
                              echo ' alunos';
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:34%; display: inline-block">
            <label for="consumo" style="font-family: Franklin Gothic Medium; margin-left:15px;">Quantidade máxima de alunos</label>
            <input type="text" name="consumo" id="consumo" readonly="readonly"
                    value="<?php
                            echo '0 alunos';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>


        <div style="width:100%; min-width:100px; display: inline-block">
          <input type="submit" name="send" value="Enviar 02" style="width:200px; margin:0 44.5%; margin-top:10px">
        </div>
      </form>
    </div>

    <div class="form_box">
      <!-- Ex3 a -->
      <form action="" method="post">
        <h2>Exercício 3 - Área do trapézio e Volume da pirâmide</h2>
        <?php
          //trapezio
          static $tb_menor = 17;
          static $tb_maior = 28;
          static $theight = 30;
        ?>
        <h3>Área do Trapézio</h3>

        <div style="width:25%; display: inline-block">
          <label for="tb_maior" style="font-family: Franklin Gothic Medium; margin-left:15px;">Base maior (cm)</label>
          <input type="text" name="tb_maior" id="tb_maior" placeholder="" readonly="readonly"
                  value="<?php
                           echo $tb_maior;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="tb_menor" style="font-family: Franklin Gothic Medium; margin-left:15px;">Base menor (cm)</label>
          <input type="text" name="tb_menor" id="tb_menor" placeholder="" readonly="readonly"
                  value="<?php
                           echo $tb_menor;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="theight" style="font-family: Franklin Gothic Medium; margin-left:15px;">Altura (cm)</label>
          <input type="text" name="theight" id="theight" placeholder="" readonly="readonly"
                  value="<?php
                           echo $theight;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($tb_maior>0 && $tb_menor>0 && $theight>0){
        ?>
          <div style="width:22%; display: inline-block">
            <label for="tarea" style="font-family: Franklin Gothic Medium; margin-left:15px;">Área (cm^2)</label>
            <input type="text" name="tarea" id="tarea" readonly="readonly"
                    value="<?php
                              echo round(($tb_maior+$tb_menor)*$theight/2, 3);
                              echo ' cm^2';
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:22%; display: inline-block">
            <label for="tarea" style="font-family: Franklin Gothic Medium; margin-left:15px;">Área (cm^2)</label>
            <input type="text" name="tarea" id="tarea" readonly="readonly"
                    value="<?php
                            echo '0 cm^2';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>

      </form>

      <!-- Ex3 b -->
      <form action="" method="post">
        <h3>Volume da Pirâmide</h3>
        <?php
          //piramide
          $pblargura = 14;
          $pbcomprimento = 18;
          $pheight = 41;
        ?>
        <div style="width:25%; display: inline-block">
          <label for="pblargura" style="font-family: Franklin Gothic Medium; margin-left:15px;">Largura da base</label>
          <input type="text" name="pblargura" id="pblargura" placeholder="" readonly="readonly"
                  value="<?php
                           echo $pblargura;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="pbcomprimento" style="font-family: Franklin Gothic Medium; margin-left:15px;">Comprimento da base (cm)</label>
          <input type="text" name="pbcomprimento" id="pbcomprimento" placeholder="" readonly="readonly"
                  value="<?php
                           echo $pbcomprimento;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="pheight" style="font-family: Franklin Gothic Medium; margin-left:15px;">Altura (cm)</label>
          <input type="text" name="pheight" id="pheight" placeholder="" readonly="readonly"
                  value="<?php
                           echo $pheight;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($pblargura>0 && $pbcomprimento>0 && $pheight>0){
        ?>
          <div style="width:22%; display: inline-block">
            <label for="pvolume" style="font-family: Franklin Gothic Medium; margin-left:15px;">Volume (cm^3)</label>
            <input type="text" name="pvolume" id="pvolume" readonly="readonly"
                    value="<?php
                              echo round($pblargura*$pbcomprimento*$pheight/3, 3);
                              echo ' cm^3';
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:22%; display: inline-block">
            <label for="pvolume" style="font-family: Franklin Gothic Medium; margin-left:15px;">Volume (cm^3)</label>
            <input type="text" name="pvolume" id="pvolume" readonly="readonly"
                    value="<?php
                            echo '0 cm^3';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>

      </form>
    </div>

    <div class="form_box">
      <!-- Ex4 -->
      <form action="" method="post">
        <h2>Exercício 4 - Classificação de Triângulo</h2>
        <?php
          $l1 = $_POST[l1];
          $l2 = $_POST[l2];
          $l3 = $_POST[l3];
        ?>
        <div style="width:25%; display: inline-block">
          <label for="l1" style="font-family: Franklin Gothic Medium; margin-left:15px;">Lado 1 (cm)</label>
          <input type="text" name="l1" id="l1" placeholder=""
                  value="<?php
                           echo $l1;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="l2" style="font-family: Franklin Gothic Medium; margin-left:15px;">Lado 2 (cm)</label>
          <input type="text" name="l2" id="l2" placeholder=""
                  value="<?php
                           echo $l2;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <div style="width:25%; display: inline-block">
          <label for="l3" style="font-family: Franklin Gothic Medium; margin-left:15px;">Lado 3 (cm)</label>
          <input type="text" name="l3" id="l3" placeholder=""
                  value="<?php
                           echo $l3;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($l1>0 && $l2>0 && $l3>0){
        ?>
          <div style="width:22%; display: inline-block">
            <label for="trtype" style="font-family: Franklin Gothic Medium; margin-left:15px;">Tipo</label>
            <input type="text" name="trtype" id="trtype" readonly="readonly"
                    value="<?php
                              if($l1==$l2 && $l2==$l3){
                                echo "Equilátero";
                              }
                              else if($l1==$l2 || $l1==$l3 || $l2==$l3){
                                echo "Isóceles";
                              }
                              else{
                                echo "Escaleno";
                              }
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:22%; display: inline-block">
            <label for="pvolume" style="font-family: Franklin Gothic Medium; margin-left:15px;">Classificação do triângulo</label>
            <input type="text" name="pvolume" id="pvolume" readonly="readonly"
                    value="<?php
                            echo '';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>

        <div style="width:100%; min-width:100px; display: inline-block">
          <input type="submit" name="send" value="Enviar 04" style="width:200px; margin:0 44.5%; margin-top:10px">
        </div>
      </form>
    </div>

    <div class="form_box">
      <!-- Ex5 -->
      <form action="" method="post">
        <h2>Exercíco 5 - Termo da Sequência de Fibonacci</h2>
        <?php
          static $termo = 12;
        ?>
        <div style="width:50%; display: inline-block">
          <label for="termo" style="font-family: Franklin Gothic Medium; margin-left:15px;">Termo</label>
          <input type="number" name="termo" id="termo" placeholder=""
                  value="<?php
                           echo $termo;
                          ?>"
          style="width:100%; text-align:center;">
        </div>

        <?php
        if($termo>0){
        ?>
          <div style="width:49%; display: inline-block">
            <label for="termoresult" style="font-family: Franklin Gothic Medium; margin-left:15px;"><?php echo "Sequência até o termo ".$termo ?></label>
            <input type="text" name="termoresult" id="termoresult" readonly="readonly"
                    value="<?php
                              $fib1=1;
                              $resultfib = '0';
                              if ($termo>=1){
                                $resultfib .= ', '.$fib1;
                              }
                              $fib2=1;
                              if ($termo>=2) $resultfib .= ', '.$fib2;
                              if ($termo>=3){
                                for ($i = 3; $i <= $termo; $i = $i + 1){
                                  $soma = $fib1 + $fib2;
                                  $fib1 = $fib2;
                                  $fib2 = $soma;
                                  $resultfib .= ', '.$fib2;
                                }
                              }
                              echo $resultfib;
                            ?>"
            style="width:100%; text-align:center; background:lightgreen;">
          </div>
        <?php
          } else if ($termo==0){
        ?>
          <div style="width:49%; display: inline-block">
            <label for="pvolume" style="font-family: Franklin Gothic Medium; margin-left:15px;"><?php echo "Sequência até o termo ".$termo ?></label>
            <input type="text" name="pvolume" id="pvolume" readonly="readonly"
                    value="<?php
                            echo '0';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          } else {
        ?>
          <div style="width:49%; display: inline-block">
            <label for="pvolume" style="font-family: Franklin Gothic Medium; margin-left:15px;"><?php echo "Sequência até o termo $ERROR" ?></label>
            <input type="text" name="pvolume" id="pvolume" readonly="readonly"
                    value="<?php
                            echo 'Termo deve ser maior que 0';
                            ?>"
            style="width:100%; text-align:center;">
          </div>
        <?php
          }
        ?>
      </form>

    </div>

  </body>
</html>
