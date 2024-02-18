import java.util.ArrayList;
import java.util.Set;

public class Main {
    public static void main(String[] args) {

        Set<String> set_vendeur = Set.of("vid", "vnom","vville");
        Tulpe v1 = new Tulpe(new String[]{"1", "Adidas", "Paris"});
        Tulpe v2 = new Tulpe(new String[]{"2", "Nike", "Nante"});
        Tulpe v3 = new Tulpe(new String[]{"3", "Supreme", "Lile"});
        Tulpe v4 = new Tulpe(new String[]{"4", "Puma", "Lyon"});
        ArrayList<Tulpe> list_vendeur = new ArrayList<>();
        list_vendeur.add(v1);
        list_vendeur.add(v2);
        list_vendeur.add(v3);
        list_vendeur.add(v4);
        Relation rv = new Relation("vendeur", set_vendeur, list_vendeur);

        Set<String> set_prod = Set.of("pid", "pnom","pville");
        Tulpe p1 = new Tulpe(new String[]{"1", "chaussure", "Shangai"});
        Tulpe p2 = new Tulpe(new String[]{"2", "pull", "Danemark"});
        Tulpe p3 = new Tulpe(new String[]{"3", "t-shirt", "Honkong"});
        Tulpe p4 = new Tulpe(new String[]{"4", "montre", "Tokyo"});
        ArrayList<Tulpe>list_prod = new ArrayList<>();
        list_prod.add(p1);
        list_prod.add(p2);
        list_prod.add(p3);
        list_prod.add(p4);
        Relation rp = new Relation("produit", set_prod, list_prod);

        Set<String> set_quant = Set.of("vid", "pid","quantite");
        Tulpe q1 = new Tulpe(new String[]{"1", "1", "100"});
        Tulpe q2 = new Tulpe(new String[]{"2", "1", "4000"});
        Tulpe q3 = new Tulpe(new String[]{"3", "1", "300"});
        Tulpe q4 = new Tulpe(new String[]{"4", "1", "200"});
        Tulpe q5 = new Tulpe(new String[]{"1", "2", "100"});
        Tulpe q6 = new Tulpe(new String[]{"4", "2", "200"});
        Tulpe q7 = new Tulpe(new String[]{"2", "3", "4000"});
        Tulpe q8 = new Tulpe(new String[]{"3", "3", "300"});
        Tulpe q9 = new Tulpe(new String[]{"4", "3", "200"});
        Tulpe q10 = new Tulpe(new String[]{"1", "4", "100"});
        Tulpe q11 = new Tulpe(new String[]{"3", "4", "300"});
        Tulpe q12 = new Tulpe(new String[]{"4", "4", "200"});
        ArrayList<Tulpe>list_quant = new ArrayList<>();
        list_quant.add(q1);
        list_quant.add(q2);
        list_quant.add(q3);
        list_quant.add(q4);
        list_quant.add(q5);
        list_quant.add(q6);
        list_quant.add(q7);
        list_quant.add(q8);
        list_quant.add(q9);
        list_quant.add(q10);
        list_quant.add(q11);
        Relation rq = new Relation("quantite", set_quant, list_quant);
        rq.addTulpe(q12);
        String[] c1 = {"vendeur.vid", "vendeur.vnom"};
        String[] c2 = {"vendeur.vid", "vendeur.vville"};
        String[] c3 = {"produit.pid", "produit.pnom"};
        String[] c4 = {"produit.pid", "produit.pville"};
        String[] c5 = {"quantite.vid", "quantite.pid","quantite.quantite"};
        String[] c6 = {"vendeur.vid", "vendeur.vville", "quantite.vid"};

        ArrayList<String[]> listc = new ArrayList<>();
        listc.add(c1);
        listc.add(c2);
        listc.add(c3);
        listc.add(c4);
        listc.add(c6);
        ArrayList<Relation> listr = new ArrayList<>();
        listr.add(rv);
        listr.add(rp);
        listr.add(rq);

        Database d = new Database(listr, listc);

        d.addContrainte(c5);

        String[] c1tmp = {"vid", "vnom"};
        String[] c2tmp = {"vid", "vville"};
        String[] c3tmp = {"pid", "pnom"};
        String[] c4tmp = {"pid", "pville"};
        String[] c5tmp = {"vid", "pid","quantite"};
        String[] c6tmp = {"vid", "vville","vid"};

        System.out.print("test TGD c6: ");
        System.out.println(d.StandardChaseTGD(rv, rq, c6tmp));

        System.out.print("test EGD c1: ");
        System.out.println(d.StandardChaseEGD(rv, c1tmp));
        System.out.print("test EGD c2: ");
        System.out.println(d.StandardChaseEGD(rv, c2tmp));
        System.out.print("test EGD c3: ");
        System.out.println(d.StandardChaseEGD(rp, c3tmp));
        System.out.print("test EGD c4: ");
        System.out.println(d.StandardChaseEGD(rp, c4tmp));
        System.out.print("test EGD c5.1: ");
        System.out.println(d.StandardChaseEGD(rq, c5tmp));
        System.out.print("test EGD c5.2: ");
        System.out.println(d.StandardChaseEGD(rq, c5tmp));



        Chase c = new Chase(d);
        System.out.print("test stdChase: ");

        System.out.println(c.StandardChase(0, c.base.contraintes));



    }
}