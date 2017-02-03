<html>
    <body>

<?php

    $morada = $_REQUEST['morada'];
    $codigo = $_REQUEST['codigo'];
    $codigoEspaco = $_REQUEST['codigoEspaco'];
    $foto = $_REQUEST['foto'];


    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180996";
        $password = "banana";
        $dbname = $user;
        $db = new PDO("mysql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        $sql1 = "INSERT INTO alugavel VALUES ('$morada', '$codigo', '$foto');";
        $sql2 = "INSERT INTO posto VALUES ('$morada', '$codigo', '$codigoEspaco');";

        $db->query($sql1);
        $db->query($sql2);

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
