import java.io.File;

public class FolderIdentifierJ {

    public static boolean isDirectory(String path) {
        File file = new File(path);
        return file.isDirectory();
    }

    public static void identifyFolders(String folderPath) {
        File folder = new File(folderPath);
        if (folder.exists() && folder.isDirectory()) {
            File[] entries = folder.listFiles();
            if (entries != null) {
                for (File entry : entries) {
                    if (!entry.isHidden()) {
                        String fullPath = entry.getAbsolutePath();
                        if (isDirectory(fullPath)) {
                            System.out.println(entry.getName() + " este folder.");
                        } else {
                            System.out.println(entry.getName() + " nu este folder.");
                        }
                    }
                }
            }
        } else {
            System.err.println("Eroare la deschiderea directorului: " + folderPath);
        }
    }

    public static void main(String[] args) {
        String folderPath = "P:/anatomie"; // Înlocuiește cu calea către directorul tău
        identifyFolders(folderPath);
    }
}
