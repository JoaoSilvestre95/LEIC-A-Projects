<html>
    <body>
        <h3>Criar Nova Reserva</h3>
        <form action="new_Reserva_script.php" method="post">
            <p><input type="hidden"></p>
            <p>Qual a oferta que quer reservar?<p>
            <p>Morada: <input type="text" name="morada"/></p>
            <p>Codigo: <input type="text" name="codigo"/></p>
            <p>Data de Inicio da Oferta (YYYY-MM-DD): <input type="text" name="dataI"/></p>
            <p>Data de Actual da Reserva (YYYY-MM-DD): <input type="text" name="dataAct"/></p>
            <br>
            <p>O seu NIF: <input type="text" name="nif"/></p>
            <p>Numero da Reserva: <input type="text" name="numero"/></p>
            <p><input type="submit" value="Submit"/></p>
        </form>
        <form action="../index.html">
          <input type="submit" value="Voltar" />
        </form>
    </body>
</html>
