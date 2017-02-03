<html>
    <body>
        <h3>Criar Nova Oferta</h3>
        <form action="new_Oferta_script.php" method="post">
            <p><input type="hidden"></p>
            <p>Morada: <input type="text" name="morada"/></p>
            <p>Codigo: <input type="text" name="codigo"/></p>
            <p>Data de Inicio (YYYY-MM-DD): <input type="text" name="dataI"/></p>
            <p>Data de Fim (YYYY-MM-DD): <input type="text" name="dataF"/></p>
            <p>Tarifa: <input type="text" name="tarifa"/></p>
            <p><input type="submit" value="Submit"/></p>
        </form>
        <form action="../index.html">
          <input type="submit" value="Voltar" />
        </form>
    </body>
</html>
