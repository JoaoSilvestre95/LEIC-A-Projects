<html>
    <body>
<?php

    $morada = $_REQUEST['morada'];
    $codigo = $_REQUEST['codigo'];
    $dataI = $_REQUEST['dataI'];
    $dataAct = $_REQUEST['dataAct'];
    $nif = $_REQUEST['nif'];
    $numero = $_REQUEST['numero'];

    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180996";
        $password = "banana";
        $dbname = $user;
        $db = new PDO("mysql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");


        $sql1 = "INSERT INTO reserva VALUES('$numero');";
        $sql2 = "INSERT INTO aluga VALUES('$morada','$codigo', '$dataI','$nif', '$numero');";
        $sql3 = "INSERT INTO estado VALUES('$numero','$dataAct', 'Aceite');";

        $db->query($sql1);
        $db->query($sql2);
        $db->query($sql3);

        $db->query("commit;");

        echo("<p>Sucesso!</p>");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>Ocorreu um erro na base de dados com o codigo: {$e->getMessage()}</p>");
    }
?>
      <form action="../index.html">
        <input type="submit" value="Voltar" />
      </form>
    </body>
</html>
