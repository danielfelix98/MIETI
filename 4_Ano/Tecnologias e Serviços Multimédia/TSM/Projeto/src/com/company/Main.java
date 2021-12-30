package com.company;
import java.io.*;
import java.util.HashMap;

public class Main {

    private static HashMap<String,Integer> Stats = new HashMap<>();

    public static void main(String[] args) throws IOException {
        FileReader paths = new FileReader(new File("/home/rafael/Documentos/videos/lol.txt"));
        BufferedReader buffer = new BufferedReader(paths);
        String path;


        while((path = buffer.readLine()) != null) { // if no more lines the readLine() returns null
            File folder = new File(path);
            System.out.println("****************");
            System.out.println("Path: "+path);
            Stats = listFilesForFolder(folder);
            BufferedWriter out = new BufferedWriter(new FileWriter(path+"/_type.txt"));
            Stats.forEach((k, v) -> {
                try {
                    out.write("." + k + " : " + v+"\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });
            out.close();
            Stats.clear();
        }
    }

    private static HashMap<String, Integer> listFilesForFolder(File folder){
        String extension;
        for (final File fileEntry : folder.listFiles()){
            if (fileEntry.isFile()) {
                System.out.println(fileEntry.getName());
                extension = fileEntry.getName();
                int j = extension.lastIndexOf(".");
                if(j > 0) {
                    extension = extension.substring(j + 1);
                    Stats.merge(extension, 1, Integer::sum);
                }
            }
        }
        return Stats;
    }
}
